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
	WSACleanup();
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

bool Client::connectToSrv(const char* srvIp, int srvPort)
{
	SOCKADDR_IN srvaddr;
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(srvPort);
	inet_pton(AF_INET, srvIp, &srvaddr.sin_addr);

	int connectSrv = connect(m_Client, (sockaddr*)&srvaddr, sizeof(srvaddr));
	if (connectSrv == SOCKET_ERROR)
		return false;

	const char* authentication = "Botmaster";
	if (sendToSrv(authentication, strlen(authentication)))	//TODO with public key on server
	{
		m_Connected = true;
		return true;
	}
	else
		return false;
}

bool Client::closeConnection()
{
	m_Connected = false;
	//m_Event = WSACreateEvent();
	shutdown(m_Client, SD_SEND);
	int disconnect = recv(m_Client, nullptr, 0, 0);
	if(disconnect == 0)
		std::cout << "Disconnected succesfully" << std::endl;
	else if(disconnect == SOCKET_ERROR)
		std::cout << "Disconnected unsuccesfully" << std::endl;

	closesocket(m_Client);
	return true;
}

bool Client::sendToSrv(const char* msg , int size)
{
	int sended = send(m_Client, msg, size, 0);
	if (sended == SOCKET_ERROR)
		return false;
	return true;
}

bool Client::receiveFromServer()
{
	if (m_Connected)
	{
		SecureZeroMemory(m_Buf, sizeof(m_Buf));
		int received = recv(m_Client, m_Buf, sizeof(m_Buf), 0);
		if (received == SOCKET_ERROR)	//received == 0 means that the connection got closed gracefully
		{
			std::cout << "SOCKET ERROR" << WSAGetLastError() << std::endl;
			return false;
		}
		else if (received == 0)
		{
			std::cout << "Disconnected succesfully" << std::endl;
			return false;
		}
		return true;
	}
	return false;
}

const char* Client::getSrvMsg()
{
	return m_Buf;
}
