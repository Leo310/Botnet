#include "BMpch.h"
#include "ResourceManager.h"

#include "Renderer.h"
#include "Platform - API/OpenGL/OpenGLResourceManager.h"

namespace GUI
{
	RecourceManager* RecourceManager::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			assert(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLResourceManager();
		}

		assert(false, "Unknown RendererAPI");
		return nullptr;
	}
}
