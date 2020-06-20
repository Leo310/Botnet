#include <iostream>
#include <thread>

#include "Client.h"

static std::string rcvMsg;

void waitingForServerMsg(Client& Botmaster)
{
	while (true)
	{
		if (Botmaster.receiveFromServer())
			std::cout << Botmaster.getSrvMsg() << std::endl;
	}
}

int main()
{
	std::cout << "Init Botmaster" << std::endl;

	Client Botmaster;

	if (!Botmaster.init())
		return 0;

	if (Botmaster.createSocket())
	{
		if (Botmaster.connectToSrv("127.0.0.1", 54001))
		{
			std::cout << "connected" << std::endl;
			std::thread worker(waitingForServerMsg, std::ref(Botmaster));
			while (true)
			{
				std::string userInput;
				std::getline(std::cin, userInput);
				if (!userInput.empty())
				{
					Botmaster.sendToSrv(userInput);
				}
			}
			worker.detach();
		}
		else
		{
			std::cout << "Couldnt connect to srv" << std::endl;
		}
	}
	else
	{
		std::cout << "Couldnt create Socket" << std::endl;
	}

	std::cin.get();
	return 0;
}