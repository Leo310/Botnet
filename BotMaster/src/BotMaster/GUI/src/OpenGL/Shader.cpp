#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
    : m_Id(0)
{
        loadShaders(vertexPath, fragmentPath);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_Id));
}

void Shader::loadShaders(const char* vertexPath, const char* fragmentPath)
{
    unsigned int vertexShader = createShader(parseShader(vertexPath).c_str(), GL_VERTEX_SHADER);
    unsigned int fragmentShader = createShader(parseShader(fragmentPath).c_str(), GL_FRAGMENT_SHADER);

    GLCall(m_Id = glCreateProgram());
    GLCall(glAttachShader(m_Id, vertexShader));
    GLCall(glAttachShader(m_Id, fragmentShader));
    GLCall(glLinkProgram(m_Id));
    int success;
    GLCall(glGetProgramiv(m_Id, GL_LINK_STATUS, &success));
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
        std::cout << "shaderprogram failed " << infoLog << std::endl;
    }
    GLCall(glValidateProgram(m_Id));
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
}

void Shader::bind()
{
    GLCall(glUseProgram(m_Id));
}

void Shader::unbind()
{
    GLCall(glUseProgram(0));
}


void Shader::setBool(const std::string& name, bool value)
{
    GLCall(glUniform1i(getUniformLocation(name), (int)value));
}

void Shader::setFloat(const std::string& name, float value)
{
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setInt(const std::string& name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setMat4(const std::string& name, glm::mat4 matrix)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

std::string Shader::parseShader(const char* path)
{
    std::stringstream shaderStream;

    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(path);

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();
  
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Error shader file could not be successfully read" << std::endl;
    }
    return shaderStream.str();
}

unsigned int Shader::createShader(const char* source, unsigned int type)
{
    GLCall(unsigned int shader = glCreateShader(type));
    GLCall(glShaderSource(shader, 1, &source, NULL));
    GLCall(glCompileShader(shader));

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "vertexShadercompilation failed " << infoLog << std::endl;
        return 0;
    }

    return shader;
}

int Shader::getUniformLocation(const std::string& name)
{
    if (uniformcache.find(name) != uniformcache.end())
        return uniformcache[name];

    GLCall(int location = glGetUniformLocation(m_Id, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesnt exist" << std::endl;

    uniformcache[name] = location;
    return location;
}
