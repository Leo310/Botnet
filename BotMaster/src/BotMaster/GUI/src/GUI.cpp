#include "BMpch.h"
#include "GUI.h"

#include "BotMaster/Core/Base.h"

namespace GUI
{
	GUI::GUI(int width, int height, const char* name)
		: m_Window(0), m_Width(width), m_Height(height), m_Title(name), m_State(GUIState::ACTIVE)
	{
	}

	GUI::~GUI()
	{
	}

	int GUI::Init()
	{
		int success = glfwInit();
		BM_ASSERT(success, "Couldnt in�t GLFW")


		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		BM_ASSERT(m_Window, "Window couldnt be created")
		BM_LOG_INFO("Created Window")

		glfwMakeContextCurrent(m_Window);

		success != glewInit();
		BM_ASSERT(success, "Coudlnt init GLEW")

		glfwSwapInterval(1);
		/*
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetCursorPosCallback(m_Window, mouse_callback);
		*/
		//Texture texture1;
		//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//Texture texture2("src/GUI/res/textures/awesomeface.png", GL_RGBA);
		//texture1.loadTexture("src/BotMaster/GUI/res/textures/container.jpg", GL_RGB);
		//quad.setTexture(texture1);
		//quad.onattach();

		//shader.loadShaders("src/BotMaster/GUI/res/Shaders/Vertex.shader", "src/BotMaster/GUI/res/Shaders/Fragment.shader");

		//shader.bind();
		//GLCall(glBindTextureUnit(0, quad.getTexture().getId()));
		float vertices[] = {
		-0.5f,-0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,-0.5,0.0f,			0.0f, 1.0f, 0.0f, 1.0f,
		0.5f,0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f, 1.0f
		};
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vertexBuffer.reset(VertexBuffer::Create(vertices, 6 * 4 * sizeof(float)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Pos"},
			{ShaderDataType::Float4, "a_Col"}
		};
		vertexBuffer->SetLayout(layout);

		const auto& Layout = vertexBuffer->GetLayout();
		unsigned int index = 0;
		for (const auto& element : Layout)
		{
			GLCall(glEnableVertexAttribArray(index));
			GLCall(glVertexAttribPointer(index, element.GetElementCount(), GL_FLOAT, element.Normalized ? GL_TRUE : GL_FALSE, Layout.GetStride(), (const void*)element.Offset));
			index++;
		}

		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		//glEnableVertexAttribArray(1);

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};
		indexBuffer.reset(IndexBuffer::Create(indices, 6));

		rManage.reset(RecourceManager::Create());
		rManage->LoadShader("src/BotMaster/GUI/assets/Shaders/Vertex.shader", "src/BotMaster/GUI/assets/Shaders/Fragment.shader", "test");

		return 1;
	}

	void GUI::update()
	{
		float time = glfwGetTime();
		deltaTime = time - lastTime;
		lastTime = time;

		//shader.bind();

		cam.setPosition({ 0.0f, 0.0f, 3.0f });
		cam.setRotation({ 0.0f, 0.0f, 0.0f });

		/*
		glm::vec4 test = glm::vec4(1.0f, 1.0f, -3.0f, 1.0f);
		test = view * test;
		std::cout << test.z << std::endl;
		*/

		//shader.setMat4("model", quad.getModelMatrix());
		//shader.setMat4("model", glm::mat4(1.0f));
		//shader.setMat4("projectionview", cam.getProjectionViewMatrix());

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
		//shader.bind();
		rManage->GetShader("test")->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, 0));

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
}