#include "GUI.h"


GUI::GUI(int width, int height, const char* name)
	: m_Window(0), m_Width(width), m_Height(height), m_Title(name), m_State(GUIState::ACTIVE)
{
	
}

GUI::~GUI()
{
}

int GUI::Init()
{
	if (!glfwInit())
	{
		std::cout << "couldnt init glfw" << std::endl;
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_Window)
	{
		std::cout << "couldnt create window" << std::endl;
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew Error!" << std::endl;
		glfwTerminate();
		return 0;
	}

	glfwSwapInterval(1);
	/*
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	*/
	Texture texture1;
	//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Texture texture2("src/GUI/res/textures/awesomeface.png", GL_RGBA);
	texture1.loadTexture("src/BotMaster/GUI/res/textures/container.jpg", GL_RGB);
	//quad.setTexture(texture1);
	//quad.onattach();

	shader.loadShaders("src/BotMaster/GUI/res/Shaders/Vertex.shader", "src/BotMaster/GUI/res/Shaders/Fragment.shader");


	quad.setTexture(texture1);
	quad.setHeight(1.0f);
	quad.setWidth(1.0f);
	quad.onattach();
	
	shader.bind();
	//GLCall(glBindTextureUnit(0, quad.getTexture().getId()));
	return 1;
}

void GUI::update()
{
	float time = glfwGetTime();
	deltaTime = time - lastTime;
	lastTime = time;


	shader.bind();


	cam.setPosition({ 0.0f, 0.0f, 3.0f });
	cam.setRotation({ 0.0f, 0.0f, 0.0f });

	/*
	glm::vec4 test = glm::vec4(1.0f, 1.0f, -3.0f, 1.0f);
	test = view * test;
	std::cout << test.z << std::endl;
	*/

	//shader.setMat4("model", quad.getModelMatrix());
	shader.setMat4("model", glm::mat4(1.0f));
	shader.setMat4("projectionview", cam.getProjectionViewMatrix());

	
	//GLCall(glActiveTexture(GL_TEXTURE0));
	//quad.getTexture().bind();
	//GLCall(glActiveTexture(GL_TEXTURE1));
	//texture2.bind();

	/*if (Eventhandler::Keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(m_Window, true);*/
}

void GUI::render()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	//texture1.bind();
	shader.bind();
	quad.update();
	GLCall(glDrawElements(GL_TRIANGLES, quad.getIndexBuffer().getCount(), GL_UNSIGNED_INT, 0));

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

GLFWwindow* GUI::getWindow()
{
	return m_Window;
}

int GUI::getWidht()
{
	return m_Width;
}

int GUI::getHeight()
{
	return m_Height;
}

