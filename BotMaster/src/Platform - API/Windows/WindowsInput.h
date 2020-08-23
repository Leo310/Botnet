#pragma once

#include "src/Input.h"

namespace GUI
{
	class WindowsInput : public Input
	{
	public:
		bool IsKeyPressedImpl(KeyCode keyCode) override;
		virtual bool IsMouseButtonPressedImpl(MouseCode mouseCode) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual bool GetMouseXImpl() override;
		virtual bool GetMouseYImpl() override;
	};
}