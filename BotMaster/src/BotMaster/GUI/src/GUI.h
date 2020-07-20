#pragma once

#include "Base.h"

#include "OpenGL/VertexArray.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "PerspectiveCamera.h"

#include "Quad.h"

enum class GUIState
{
	ACTIVE = 1
};

class GUI
{
public:
	GUI(int width, int height, const char* name);
	~GUI();

	int Init();
	void update();
	void render();

	GLFWwindow* getWindow();
	int getWidht();
	int getHeight();

private:

	GLFWwindow* m_Window;
	int m_Width, m_Height;
	const char* m_Title;

	GUIState m_State;

	//Testing
	Shader shader;
	PerspectiveCamera cam;
	Quad quad;


	float lastTime = 0.0f;
	float deltaTime = 0.0f;

};