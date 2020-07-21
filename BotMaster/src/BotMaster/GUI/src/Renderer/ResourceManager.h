#pragma once

#include <string>
#include "Shader.h"
#include <memory>

namespace GUI
{
	class RecourceManager
	{
	public:
		virtual ~RecourceManager() {};

		virtual Shader* LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const std::string& name) = 0;
		virtual Shader* GetShader(const std::string& name) = 0;

		virtual void Clear() = 0;

		static RecourceManager* Create();
	
	};
}