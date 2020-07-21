#pragma once

#include "src/Renderer/Shader.h"

namespace GUI
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexShaderSource, const char* fragmentShaderSource);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		//uniforms
		virtual void SetBool(const char* name, bool value);
		virtual void SetFloat(const char* name, float value);
		virtual void SetInt(const char* name, int value);
		//virtual void setMat4(const char* name, glm::mat4 matrix) = 0;

	private:
		unsigned int m_RendererId;
		std::unordered_map<std::string, int> m_Uniformcache;

		unsigned int CompileShader(const char* source, unsigned int type);
		int GetUniformLocation(const char* name);
	};
}