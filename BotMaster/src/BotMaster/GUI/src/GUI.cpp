#include "BMpch.h"
#include "GUI.h"

#include "BotMaster/Core/Base.h"

#include "ImGui/ImGuiLayer.h"
#include "Input.h"

class ExampleLayer : public GUI::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void Update() override
	{
		BM_LOG_INFO("update {0}", GetName());
	}

	void OnEvent(GUI::Event& event) override
	{
		BM_LOG_TRACE("ExampleLayer {0}", event.ToString());
	}
};

namespace GUI
{

	GUI* GUI::s_Instance = nullptr;

	GUI::GUI(int width, int height, const char* name)
	{
		BM_ASSERT(!s_Instance, "GUI already exist");
		s_Instance = this;
		window.reset(Window::Create(WindowProperties(name, width, height, true)));
		window->SetEventCallback(BIND_EVENT_FN(GUI::OnEvent));
	}

	GUI::~GUI()
	{
	}

	int GUI::Init()
	{
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


		//layerstack.PushLayer(new ExampleLayer());
		ImGuiLayer* imgui = new ImGuiLayer();
		imgui->Attach();
		layerstack.PushOverlay(imgui);

		return 1;
	}

	void GUI::Update()
	{
		auto [x, y] = Input::GetMousePos();
		BM_LOG_TRACE("{0}, {1}", x, y);
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

	void GUI::Render()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		//texture1.bind();
		//shader.bind();
		for (Layer* layer : layerstack)
			layer->Update();
		rManage->GetShader("test")->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, 0));
		window->Update(); 
	}

	void GUI::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(GUI::OnWindowClosed));
		//BM_LOG_TRACE("Core {0}", e.ToString());

		for (auto it = layerstack.end(); it != layerstack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool GUI::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}