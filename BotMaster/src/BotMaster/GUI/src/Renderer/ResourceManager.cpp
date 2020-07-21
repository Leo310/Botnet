#include "BMpch.h"
#include "ResourceManager.h"

#include "Renderer.h"
#include "BotMaster/Core/Base.h"
#include "Platform - API/OpenGL/OpenGLResourceManager.h"

namespace GUI
{
	RecourceManager* RecourceManager::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			BM_ASSERT(false, "RendererAPI::NONE is currently not supported")
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLResourceManager();
		}

		BM_ASSERT(false, "Unknown RendererAPI")
		return nullptr;
	}
}
