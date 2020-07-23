#include "BMpch.h"
#include "Window.h"
#include "Platform - API/Windows/WindowsWindow.h"

namespace GUI
{
	Window* Window::Create(const WindowProperties& props)
	{
#ifdef BM_PLATFORM_WINDOWS
		return new WindowsWindow(props);
#elif // BM_PLATFORM_WINDOWS
		BM_ASSERT(false, "Unknown platform");
		return nullptr;
#endif
	}
}
