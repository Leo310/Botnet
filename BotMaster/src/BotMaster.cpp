#include <iostream>

#include "Client.h"

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