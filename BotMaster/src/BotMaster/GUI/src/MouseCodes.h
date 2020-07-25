#pragma once

#include <BMpch.h>

namespace GUI
{
	typedef enum class MouseCode : unsigned short
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;	

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int>(mouseCode);
		return os;
	}
}

#define BM_MOUSE_BUTTON_0      ::GUI::Mouse::Button0
#define BM_MOUSE_BUTTON_1      ::GUI::Mouse::Button1
#define BM_MOUSE_BUTTON_2      ::GUI::Mouse::Button2
#define BM_MOUSE_BUTTON_3      ::GUI::Mouse::Button3
#define BM_MOUSE_BUTTON_4      ::GUI::Mouse::Button4
#define BM_MOUSE_BUTTON_5      ::GUI::Mouse::Button5
#define BM_MOUSE_BUTTON_6      ::GUI::Mouse::Button6
#define BM_MOUSE_BUTTON_7      ::GUI::Mouse::Button7
#define BM_MOUSE_BUTTON_LAST   ::GUI::Mouse::ButtonLast
#define BM_MOUSE_BUTTON_LEFT   ::GUI::Mouse::ButtonLeft
#define BM_MOUSE_BUTTON_RIGHT  ::GUI::Mouse::ButtonRight
#define BM_MOUSE_BUTTON_MIDDLE ::GUI::Mouse::ButtonMiddle