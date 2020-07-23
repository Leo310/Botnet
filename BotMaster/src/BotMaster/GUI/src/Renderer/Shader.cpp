#include "BMpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "BotMaster/Core/Base.h"
#include "Platform - API/OpenGL/OpenGLShader.h"

namespace GUI
{
	Shader* Shader::Create(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			BM_ASSERT(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexShaderSource, fragmentShaderSource);
		}

		BM_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
