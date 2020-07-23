#include "BMpch.h"

#include "OpenGLResourceManager.h"
#include "OpenGLBase.h"


namespace GUI
{
    Shader* OpenGLResourceManager::LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const std::string& name)
    {
        std::string vertex = ParseShader(vertexShaderPath);
        std::string fragment= ParseShader(fragmentShaderPath);
        m_Shaders[name] = Shader::Create(vertex.c_str(), fragment.c_str());
        return m_Shaders[name];
    }

    Shader* OpenGLResourceManager::GetShader(const std::string& name)
    {
       return m_Shaders[name];
    }

    void OpenGLResourceManager::Clear()
    {
        //m_Shaders.clear();
    }

    std::string OpenGLResourceManager::ParseShader(const char* path)
    {
        std::string Code;

        try
        {
            // open files
            std::ifstream ShaderFile(path);
            std::stringstream ShaderStream;
            // read file's buffer contents into streams
            ShaderStream << ShaderFile.rdbuf();

            // close file handlers
            ShaderFile.close();
            // convert stream into string
            Code = ShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
        }
        catch (std::exception e)
        {
            BM_LOG_ERROR("ERROR::SHADER: Failed to read shader files");
        }
        
        return Code;
    }
}