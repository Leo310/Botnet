#pragma once

#include "Platform - API/OpenGL/Base.h"

#include "PerspectiveCamera.h"

#include "Renderer/Buffer.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Shader.h"

namespace GUI
{
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
		PerspectiveCamera cam;

		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<IndexBuffer> indexBuffer;
		std::unique_ptr<RecourceManager> rManage;

		float lastTime = 0.0f;
		float deltaTime = 0.0f;

	};
}
