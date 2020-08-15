#pragma once

namespace GUI
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;

		WindowProperties(const std::string& title = "Botmaster", unsigned int width = 1920, unsigned int height = 1080, bool vsync = false)
			: Title(title), Width(width), Height(height), VSync(vsync){}
	};

	class Event;

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}
		virtual void Update() = 0;
	
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}