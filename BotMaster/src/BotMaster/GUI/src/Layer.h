#pragma once

#include "Events/Event.h"

namespace GUI
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		~Layer();

		virtual void Attach() {}
		virtual void Detach() {}
		virtual void Update() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}