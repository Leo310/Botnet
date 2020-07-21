#pragma once

#include "BotMaster/Core/Base.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "stb_image.h"

#define GLCall(x) GLClearError();\
    x;\
    BM_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "");

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);