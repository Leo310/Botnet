#include "BMpch.h"
#include "GUI.h"

#include "BotMaster/Core/Base.h"

int main()
{
	{
		Log::Init();
		BM_LOG_ERROR("test");
		GUI::GUI gui(1920, 1080, "Botmaster");

		int success = gui.Init();
		BM_ASSERT(success, "Couldnt init GUI")

		while (!glfwWindowShouldClose(gui.getWindow()))
		{
			//gui.update();
			gui.render();

		}

	}
	glfwTerminate();

	return 0;
}

