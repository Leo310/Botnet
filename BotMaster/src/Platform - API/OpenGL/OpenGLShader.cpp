#include "BMpch.h"

#include "OpenGLShader.h"

#include "Base.h"

namespace GUI
{
    OpenGLShader::OpenGLShader(const char* vertexShaderSource, const char* fragmentShaderSource)
    {
        unsigned int vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
        unsigned int fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        GLCall(m_RendererId = glCreateProgram());
        GLCall(glAttachShader(m_RendererId, vertexShader));
        GLCall(glAttachShader(m_RendererId, fragmentShader));
        GLCall(glLinkProgram(m_RendererId));
        int success;
        GLCall(glGetProgramiv(m_RendererId, GL_LINK_STATUS, &success));
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_RendererId, 512, NULL, infoLog);
            std::cout << "shaderprogram failed " << infoLog << std::endl;
        }
        GLCall(glValidateProgram(m_RendererId));
        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));
    }

    OpenGLShader::~OpenGLShader()
    {
        GLCall(glDeleteProgram(m_RendererId));
    }

    void OpenGLShader::Bind() const
    {
        GLCall(glUseProgram(m_RendererId));
    }

    void OpenGLShader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    unsigned int OpenGLShader::CompileShader(const char* source, unsigned int type)
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
            std::cout << "Shadercompilation failed " << infoLog << std::endl;
            return 0;
        }

        return shader;
    }


    void OpenGLShader::SetBool(const char* name, bool value)
    {
        GLCall(glUniform1i(GetUniformLocation(name), (int)value));
    }

    void OpenGLShader::SetFloat(const char* name, float value)
    {
        GLCall(glUniform1f(GetUniformLocation(name), value));
    }

    void OpenGLShader::SetInt(const char* name, int value)
    {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }
    /*
    void OpenGLShader::SetMat4(const char* name, glm::mat4 matrix)
    {
        GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
    }
    */

    int OpenGLShader::GetUniformLocation(const char* name)
    {
        if (m_Uniformcache.find(name) != m_Uniformcache.end())
            return m_Uniformcache[name];

        GLCall(int location = glGetUniformLocation(m_RendererId, name));
        if (location == -1)
            std::cout << "Warning: uniform '" << name << "' doesnt exist" << std::endl;

        m_Uniformcache[name] = location;
        return location;
    }
}
