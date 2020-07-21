#pragma once

#include "src/Renderer/ResourceManager.h"

namespace GUI
{
	class OpenGLResourceManager : public RecourceManager
	{
	public:
		OpenGLResourceManager() {};
		virtual ~OpenGLResourceManager() {};


		virtual Shader* LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const std::string& name);
		virtual Shader* GetShader(const std::string& name);

		virtual void Clear();

	private:
		std::string ParseShader(const char* path);
		std::unordered_map<std::string, Shader*> m_Shaders;
	};
}