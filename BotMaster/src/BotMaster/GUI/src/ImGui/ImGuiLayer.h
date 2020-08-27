#pragma once

#include "src/Layer.h"
#include "src/Events/KeyEvent.h"
#include "src/Events/MouseEvent.h"
#include "src/Events/ApplicationEvent.h"


namespace GUI
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void Attach() override;
		virtual void Detach() override;

		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time;
	};
}