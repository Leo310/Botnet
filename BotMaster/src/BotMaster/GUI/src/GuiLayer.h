#pragma once

#include "Layer.h"
#include "Events/Event.h"

namespace GUI
{
	class GuiLayer : public Layer
	{
	public:
		virtual void Attach() override;
		virtual void Detach() override;
		virtual void Update() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

		bool DDoS = false;
	};
}