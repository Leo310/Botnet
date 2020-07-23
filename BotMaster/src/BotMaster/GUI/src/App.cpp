#include "BMpch.h"
#include "GUI.h"

#include "BotMaster/Core/Base.h"

int main()
{
	
	Log::Init();
	GUI::GUI gui(1920, 1080, "Botmaster");
	gui.Init();


	while (!gui.Exit())
	{
		//gui.update();
		gui.Render();

	}
	return 0;
}

