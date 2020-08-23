#pragma once

#include "src/KeyCodes.h"
#include "src/MouseCodes.h"

namespace GUI 
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

		inline static bool IsMouseButtonPressed(MouseCode mouseCode) { return s_Instance->IsMouseButtonPressedImpl(mouseCode); }

		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode mouseCode) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual bool GetMouseXImpl() = 0;
		virtual bool GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}