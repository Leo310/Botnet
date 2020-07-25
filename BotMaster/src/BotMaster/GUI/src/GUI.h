#pragma once

#include "Platform - API/OpenGL/OpenGLBase.h"

#include "PerspectiveCamera.h"

#include "Renderer/Buffer.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Shader.h"
#include "Window.h"
#include "Events/Event.h"

namespace GUI
{
	class GUI
	{
	public:
		GUI(int width, int height, const char* name);
		~GUI();

		int Init();
		void Update();
		void Render();

		void OnEvent(Event& e);

		inline bool IsRunning() const { return m_Running; };

	private:

		//Testing
		PerspectiveCamera cam;

		bool m_Running = true;

		std::unique_ptr<Window> window;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<IndexBuffer> indexBuffer;
		std::unique_ptr<RecourceManager> rManage;

		float lastTime = 0.0f;
		float deltaTime = 0.0f;

	};
}
