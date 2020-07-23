#include "BMpch.h"
#include "WindowsWindow.h"
#include "src/Renderer/Renderer.h"

namespace GUI
{
	static unsigned int s_GLFWwindowCount = 0;

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Update()
	{
		m_Exit = glfwWindowShouldClose(m_Window);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		if (s_GLFWwindowCount == 0)
		{
			m_WindowProperties = props;
			int success = glfwInit();
			BM_ASSERT(success, "Couldnt inít GLFW");

			BM_LOG_INFO("Init GLFW");

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			
		}

#if defined(BM_DEBUG)
		if (Renderer::GetAPI() == RendererAPI::OpenGL)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_Window = glfwCreateWindow(m_WindowProperties.Width, m_WindowProperties.Height, m_WindowProperties.Title.c_str(), NULL, NULL);
		BM_ASSERT(m_Window, "Window couldnt be created");
		BM_LOG_INFO("Created window {0} ({1}, {2})", m_WindowProperties.Title, m_WindowProperties.Width, m_WindowProperties.Height);
		glfwMakeContextCurrent(m_Window);

		if (s_GLFWwindowCount == 0)
		{
			int success = !glewInit();
			BM_ASSERT(success, "Couldnt init GLEW");
		}
		s_GLFWwindowCount++;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		s_GLFWwindowCount--;
		if (s_GLFWwindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
			BM_LOG_INFO("Enabled VSync");
		}
		else
		{
			glfwSwapInterval(0);
			BM_LOG_INFO("Disabled VSync");
		}
		m_WindowProperties.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_WindowProperties.VSync;
	}
}
