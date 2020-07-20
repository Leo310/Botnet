#include "GUI.h"

int main()
{
	{

		GUI gui(1920, 1080, "Botmaster");
		if (!gui.Init())
		{
			std::cout << "Couldnt init GUI" << std::endl;
			std::cin.get();
			return -1;
		}

	

		while (!glfwWindowShouldClose(gui.getWindow()))
		{
			//gui.update();
			gui.render();

		}

	}
	glfwTerminate();

	return 0;
}

