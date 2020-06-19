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

bool Server::waitForConnection()
{
	SOCKET m_Zombie = accept(m_Listening, nullptr, nullptr);
	if (m_Zombie == INVALID_SOCKET)
		return false;
	else
	{
		m_Zombies.push_back(m_Zombie);
		return true;
	}
}
