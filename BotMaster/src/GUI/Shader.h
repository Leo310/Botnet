#pragma once

#include "GL/glew.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>

#include "vendor/GLM/glm.hpp"
#include "vendor/GLM/gtc/matrix_transform.hpp"
#include "vendor/GLM/gtc/type_ptr.hpp"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Shader
{
public:

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Bind();
	void Unbind();

	//uniforms
	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setInt(const std::string& name, int value);
	void setMat4(const std::string& name, glm::mat4 matrix);
private:
	int getUniformLocation(const std::string& name);
	unsigned int m_Id;
	std::unordered_map<std::string, int> uniformcache;
};