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

		virtual unsigned int GetWidth() const override { return m_Data.Width; };
		virtual unsigned int GetHeight() const override { return m_Data.Height; };

		virtual void SetEventCallback(const EventCallbackFn& callback) ;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		void Init(const WindowProperties& props);
		void Shutdown();

		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}