#pragma once

#include "src/Layer.h"

namespace GUI
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void Attach() override;
		void Detach() override;
		void Update() override;
		void OnEvent(Event& event) override;

	private:
		float m_Time;
	};
}