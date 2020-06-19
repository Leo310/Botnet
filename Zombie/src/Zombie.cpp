#include <iostream>

#include "Client.h"

int main()
{
#ifdef RELEASE
	FreeConsole();
#endif
	std::cout << "Init Zombie" << std::endl;

	Client Zombie;

	if (!Zombie.init())
		return 0;

	if (Zombie.createSocket())
	{
		if (Zombie.connectToSrv("127.0.0.1", 54001))
		{
			std::cout << "connected" << std::endl;
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