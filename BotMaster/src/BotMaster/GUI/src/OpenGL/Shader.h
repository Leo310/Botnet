#pragma once

#include "src/Base.h"

class Shader
{
public:
	Shader()
		: m_Id(0) {}
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void loadShaders(const char* vertexPath, const char* fragmentPath);

	void bind();
	void unbind();

	//uniforms

	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setInt(const std::string& name, int value);
	void setMat4(const std::string& name, glm::mat4 matrix);
private:
	std::string parseShader(const char* path);
	unsigned int createShader(const char* source, unsigned int type);

	unsigned int m_Id;
	int getUniformLocation(const std::string& name);
	std::unordered_map<std::string, int> uniformcache;
};
