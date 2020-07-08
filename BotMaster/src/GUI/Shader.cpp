#include "Shader.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    bool noerror = true;
    while (GLenum error = glGetError() != GL_NO_ERROR)
    {
        std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << ":" << line << std::endl;
        noerror = false;
    }
    return noerror;
}


Shader::Shader(const char* vertexPath, const char* fragmentPath)
    : m_Id(0)
{

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error shader file could not be successfully read" << std::endl;
	}

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertexShader;
    GLCall(vertexShader = glCreateShader(GL_VERTEX_SHADER));
    GLCall(glShaderSource(vertexShader, 1, &vShaderCode, NULL));
    GLCall(glCompileShader(vertexShader));
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "vertexShadercompilation failed " << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    GLCall(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
    GLCall(glShaderSource(fragmentShader, 1, &fShaderCode, NULL));
    GLCall(glCompileShader(fragmentShader));
    GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "fragmentShadercompilation failed " << infoLog << std::endl;
    }

    GLCall(m_Id = glCreateProgram());
    GLCall(glAttachShader(m_Id, vertexShader));
    GLCall(glAttachShader(m_Id, fragmentShader));
    GLCall(glLinkProgram(m_Id));
    GLCall(glGetProgramiv(m_Id, GL_LINK_STATUS, &success));
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
        std::cout << "shaderprogram failed " << infoLog << std::endl;
    }
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_Id));
}

void Shader::Bind()
{
    GLCall(glUseProgram(m_Id));
}

void Shader::Unbind()
{
    GLCall(glUseProgram(0));
}

//TOdo cache uniform location

void Shader::setBool(const std::string& name, bool value) const
{
    
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_Id, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_Id, name.c_str()), value);
}
