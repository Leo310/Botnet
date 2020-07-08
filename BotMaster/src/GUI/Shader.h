#pragma once

#include "GL/glew.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

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
	void setBool(const std::string& name, bool value) const;
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
private:
	unsigned int m_Id;

};