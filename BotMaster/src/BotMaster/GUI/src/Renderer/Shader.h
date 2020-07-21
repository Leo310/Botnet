#pragma once

namespace GUI
{
	class Shader
	{
	public:
		virtual ~Shader() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		//uniforms
		virtual void SetBool(const char* name, bool value) = 0;
		virtual void SetFloat(const char* name, float value) = 0;
		virtual void SetInt(const char* name, int value) = 0;
		//virtual void setMat4(const char* name, glm::mat4 matrix) = 0;

		static Shader* Create(const char* vertexShaderSource, const char* fragmentShaderSource);
	};
}