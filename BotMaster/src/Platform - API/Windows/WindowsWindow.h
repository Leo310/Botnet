#pragma once

#include "src/Window.h"
#include "Platform - API/OpenGL/OpenGLBase.h"

namespace GUI
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		virtual void Update() override;

		virtual unsigned int getWidth() const override { return m_WindowProperties.Width; };
		virtual unsigned int getHeight() const override { return m_WindowProperties.Height; };

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual bool Exit() const override { return m_Exit; };

	private:
		void Init(const WindowProperties& props);
		void Shutdown();

		bool m_Exit = false;

		GLFWwindow* m_Window;
		WindowProperties m_WindowProperties;
	};
}