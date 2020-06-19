#pragma once

#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <string>
#include <vector>

class Server
{
public:
	Server(std::string ip, int port);
	~Server();

	bool init();
	int cleanUp();

	bool createListeningSocket();
	bool waitForConnection();

private:
	std::string m_IpAddress;
	int m_Port;

	SOCKET m_Listening;

	std::vector<SOCKET> m_Zombies;
};