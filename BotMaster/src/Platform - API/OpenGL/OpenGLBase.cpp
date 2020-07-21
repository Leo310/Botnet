#include "BMpch.h"
#include "OpenGLBase.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	bool noerror = true;
	GLenum error = 0;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << ":" << line << std::endl;
		noerror = false;
	}
	return noerror;
}