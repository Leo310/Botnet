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

	class Window
	{
	public:
		virtual ~Window() {}
		virtual void Update() = 0;
	
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual bool Exit() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}