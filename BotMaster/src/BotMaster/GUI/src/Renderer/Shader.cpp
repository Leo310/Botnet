#include "BMpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform - API/OpenGL/OpenGLShader.h"

namespace GUI
{
	Shader* Shader::Create(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::NONE:
			assert(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexShaderSource, fragmentShaderSource);
		}

		assert(false, "Unknown RendererAPI");
		return nullptr;
	}
}
