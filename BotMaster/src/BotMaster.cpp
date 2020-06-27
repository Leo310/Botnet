#include "Client.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

static std::mutex mutexMsg;
static std::condition_variable cvrcvMsg;
static std::atomic<bool> rcvMsg{ false };

static std::mutex mutexInput;
static std::condition_variable cvuserInput;
static std::string userInput;
static std::atomic<bool> userInputed{ false };


void waitingForServerMsg(Client& Botmaster)
{
	while (true)
	{
		std::unique_lock<std::mutex> ul(mutexMsg);
		rcvMsg = Botmaster.receiveFromServer();
		cvrcvMsg.wait(ul, []() { return !rcvMsg.load(); });
	}
}

void waitingForUserInput()
{
	while (true)
	{
		std::unique_lock<std::mutex> ul(mutexInput);
		std::getline(std::cin, userInput);
		userInputed = true;
		cvuserInput.wait(ul, []() { return !userInputed.load(); });
	}
}

int main()
{
	std::cout << "Init Botmaster" << std::endl;

	Client Botmaster;

	if (!Botmaster.init())
		return 0;

	if (Botmaster.createSocket())
	{
		if (Botmaster.connectToSrv("127.0.0.1", 54002))
		{
			std::cout << "connected" << std::endl;
			std::thread worker1(waitingForServerMsg, std::ref(Botmaster));
			worker1.detach();
			std::thread worker2(waitingForUserInput);
			worker2.detach();

			while (true)
			{
				if (userInputed.load())
				{
					if (userInput == "exit")
						break;
					Botmaster.sendToSrv(userInput.c_str(), userInput.size());
					userInputed = false;
					cvuserInput.notify_one();
				}

				if (rcvMsg.load())
				{
					std::cout << Botmaster.getSrvMsg() << std::endl;
					rcvMsg = false;
					cvrcvMsg.notify_one();
				}
			}
			Botmaster.closeConnection();
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