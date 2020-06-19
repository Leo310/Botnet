#include "Client.h"

Client::Client()
	: m_Client(0)
{
}

bool Client::init()
{
	WSAData data;
	return !WSAStartup(MAKEWORD(2, 2), &data);
}

Client::~Client()
{
	cleanup();
}

int Client::cleanup()
{
	closesocket(m_Client);
	return WSACleanup();
}

bool Client::createSocket()
{
	m_Client = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Client == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool Client::connectToSrv(const std::string& srvIp, int srvPort)
{
	SOCKADDR_IN srvaddr;
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(srvPort);
	inet_pton(AF_INET, srvIp.c_str(), &srvaddr.sin_addr);

	int connectSrv = connect(m_Client, (sockaddr*)&srvaddr, sizeof(srvaddr));
	if (connectSrv == SOCKET_ERROR)
		return false;
	return true;
}
