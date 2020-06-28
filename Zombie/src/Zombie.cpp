#include "Client.h"
#include "Echo.h"
#include "Standby.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

static std::condition_variable cv;
static std::mutex mutex;
//static std::atomic<bool> arcvdMsg(false);
static bool rcvdMsg = false;
std::string rcvMsg;

void waitingForServerMsg(Client& zombie)
{
	while (true)
	{
		std::unique_lock<std::mutex> ul(mutex);
		rcvdMsg = zombie.receiveFromServer();
		cv.wait(ul, []() {return !rcvdMsg; });
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
				{
					std::lock_guard lock(mutex);
					if (rcvdMsg)
					{
						rcvMsg = Zombie.getSrvMsg();
						rcvdMsg = false;
						cv.notify_one();
					}
				}
				//if (!rcvMsg.empty())

				state = state->update();
				state->run();
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