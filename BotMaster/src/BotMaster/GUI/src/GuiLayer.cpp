#include "BMpch.h"
#include "GuiLayer.h"

#include "BotMaster/Core/Base.h"
#include "imgui.h"

namespace GUI
{
	void GuiLayer::Attach()
	{
	}

	void GuiLayer::Detach()
	{
	}

	void GuiLayer::Update()
	{
	}

	void GuiLayer::OnImGuiRender()
	{
		bool show = true;
		ImGui::Begin("States");
		if (ImGui::Button("DDos"))
			BM_LOG_INFO("DDOS");
		ImGui::End();
		ImGui::ShowDemoWindow(&show);
	}

	void GuiLayer::OnEvent(Event& event)
	{
	}
}
