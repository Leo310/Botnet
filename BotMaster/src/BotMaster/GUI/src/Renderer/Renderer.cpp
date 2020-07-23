#include "BMpch.h"
#include "Renderer.h"
#include "BotMaster/Core/Base.h"

namespace GUI
{
#ifdef BM_PLATFORM_WINDOWS
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
#elif // BM_PLATFORM_WINDOWS
	RendererAPI Renderer::s_RendererAPI = RendererAPI::NONE;
#endif

}