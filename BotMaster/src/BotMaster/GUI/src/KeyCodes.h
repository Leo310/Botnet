#pragma once

#include <BMpch.h>

namespace GUI
{
	typedef enum class KeyCode : unsigned short
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int>(keyCode); 
		return os;
	}
}

// From glfw3.h
#define BM_KEY_SPACE           ::GUI::Key::Space
#define BM_KEY_APOSTROPHE      ::GUI::Key::Apostrophe    /* ' */
#define BM_KEY_COMMA           ::GUI::Key::Comma         /* , */
#define BM_KEY_MINUS           ::GUI::Key::Minus         /* - */
#define BM_KEY_PERIOD          ::GUI::Key::Period        /* . */
#define BM_KEY_SLASH           ::GUI::Key::Slash         /* / */
#define BM_KEY_0               ::GUI::Key::D0
#define BM_KEY_1               ::GUI::Key::D1
#define BM_KEY_2               ::GUI::Key::D2
#define BM_KEY_3               ::GUI::Key::D3
#define BM_KEY_4               ::GUI::Key::D4
#define BM_KEY_5               ::GUI::Key::D5
#define BM_KEY_6               ::GUI::Key::D6
#define BM_KEY_7               ::GUI::Key::D7
#define BM_KEY_8               ::GUI::Key::D8
#define BM_KEY_9               ::GUI::Key::D9
#define BM_KEY_SEMICOLON       ::GUI::Key::Semicolon     /* ; */
#define BM_KEY_EQUAL           ::GUI::Key::Equal         /* = */
#define BM_KEY_A               ::GUI::Key::A
#define BM_KEY_B               ::GUI::Key::B
#define BM_KEY_C               ::GUI::Key::C
#define BM_KEY_D               ::GUI::Key::D
#define BM_KEY_E               ::GUI::Key::E
#define BM_KEY_F               ::GUI::Key::F
#define BM_KEY_G               ::GUI::Key::G
#define BM_KEY_H               ::GUI::Key::H
#define BM_KEY_I               ::GUI::Key::I
#define BM_KEY_J               ::GUI::Key::J
#define BM_KEY_K               ::GUI::Key::K
#define BM_KEY_L               ::GUI::Key::L
#define BM_KEY_M               ::GUI::Key::M
#define BM_KEY_N               ::GUI::Key::N
#define BM_KEY_O               ::GUI::Key::O
#define BM_KEY_P               ::GUI::Key::P
#define BM_KEY_Q               ::GUI::Key::Q
#define BM_KEY_R               ::GUI::Key::R
#define BM_KEY_S               ::GUI::Key::S
#define BM_KEY_T               ::GUI::Key::T
#define BM_KEY_U               ::GUI::Key::U
#define BM_KEY_V               ::GUI::Key::V
#define BM_KEY_W               ::GUI::Key::W
#define BM_KEY_X               ::GUI::Key::X
#define BM_KEY_Y               ::GUI::Key::Y
#define BM_KEY_Z               ::GUI::Key::Z
#define BM_KEY_LEFT_BRACKET    ::GUI::Key::LeftBracket   /* [ */
#define BM_KEY_BACKSLASH       ::GUI::Key::Backslash     /* \ */
#define BM_KEY_RIGHT_BRACKET   ::GUI::Key::RightBracket  /* ] */
#define BM_KEY_GRAVE_ACCENT    ::GUI::Key::GraveAccent   /* ` */
#define BM_KEY_WORLD_1         ::GUI::Key::World1        /* non-US #1 */
#define BM_KEY_WORLD_2         ::GUI::Key::World2        /* non-US #2 */

/* Function keys */
#define BM_KEY_ESCAPE          ::GUI::Key::Escape
#define BM_KEY_ENTER           ::GUI::Key::Enter
#define BM_KEY_TAB             ::GUI::Key::Tab
#define BM_KEY_BACKSPACE       ::GUI::Key::Backspace
#define BM_KEY_INSERT          ::GUI::Key::Insert
#define BM_KEY_DELETE          ::GUI::Key::Delete
#define BM_KEY_RIGHT           ::GUI::Key::Right
#define BM_KEY_LEFT            ::GUI::Key::Left
#define BM_KEY_DOWN            ::GUI::Key::Down
#define BM_KEY_UP              ::GUI::Key::Up
#define BM_KEY_PAGE_UP         ::GUI::Key::PageUp
#define BM_KEY_PAGE_DOWN       ::GUI::Key::PageDown
#define BM_KEY_HOME            ::GUI::Key::Home
#define BM_KEY_END             ::GUI::Key::End
#define BM_KEY_CAPS_LOCK       ::GUI::Key::CapsLock
#define BM_KEY_SCROLL_LOCK     ::GUI::Key::ScrollLock
#define BM_KEY_NUM_LOCK        ::GUI::Key::NumLock
#define BM_KEY_PRINT_SCREEN    ::GUI::Key::PrintScreen
#define BM_KEY_PAUSE           ::GUI::Key::Pause
#define BM_KEY_F1              ::GUI::Key::F1
#define BM_KEY_F2              ::GUI::Key::F2
#define BM_KEY_F3              ::GUI::Key::F3
#define BM_KEY_F4              ::GUI::Key::F4
#define BM_KEY_F5              ::GUI::Key::F5
#define BM_KEY_F6              ::GUI::Key::F6
#define BM_KEY_F7              ::GUI::Key::F7
#define BM_KEY_F8              ::GUI::Key::F8
#define BM_KEY_F9              ::GUI::Key::F9
#define BM_KEY_F10             ::GUI::Key::F10
#define BM_KEY_F11             ::GUI::Key::F11
#define BM_KEY_F12             ::GUI::Key::F12
#define BM_KEY_F13             ::GUI::Key::F13
#define BM_KEY_F14             ::GUI::Key::F14
#define BM_KEY_F15             ::GUI::Key::F15
#define BM_KEY_F16             ::GUI::Key::F16
#define BM_KEY_F17             ::GUI::Key::F17
#define BM_KEY_F18             ::GUI::Key::F18
#define BM_KEY_F19             ::GUI::Key::F19
#define BM_KEY_F20             ::GUI::Key::F20
#define BM_KEY_F21             ::GUI::Key::F21
#define BM_KEY_F22             ::GUI::Key::F22
#define BM_KEY_F23             ::GUI::Key::F23
#define BM_KEY_F24             ::GUI::Key::F24
#define BM_KEY_F25             ::GUI::Key::F25

/* Keypad */
#define BM_KEY_KP_0            ::GUI::Key::KP0
#define BM_KEY_KP_1            ::GUI::Key::KP1
#define BM_KEY_KP_2            ::GUI::Key::KP2
#define BM_KEY_KP_3            ::GUI::Key::KP3
#define BM_KEY_KP_4            ::GUI::Key::KP4
#define BM_KEY_KP_5            ::GUI::Key::KP5
#define BM_KEY_KP_6            ::GUI::Key::KP6
#define BM_KEY_KP_7            ::GUI::Key::KP7
#define BM_KEY_KP_8            ::GUI::Key::KP8
#define BM_KEY_KP_9            ::GUI::Key::KP9
#define BM_KEY_KP_DECIMAL      ::GUI::Key::KPDecimal
#define BM_KEY_KP_DIVIDE       ::GUI::Key::KPDivide
#define BM_KEY_KP_MULTIPLY     ::GUI::Key::KPMultiply
#define BM_KEY_KP_SUBTRACT     ::GUI::Key::KPSubtract
#define BM_KEY_KP_ADD          ::GUI::Key::KPAdd
#define BM_KEY_KP_ENTER        ::GUI::Key::KPEnter
#define BM_KEY_KP_EQUAL        ::GUI::Key::KPEqual

#define BM_KEY_LEFT_SHIFT      ::GUI::Key::LeftShift
#define BM_KEY_LEFT_CONTROL    ::GUI::Key::LeftControl
#define BM_KEY_LEFT_ALT        ::GUI::Key::LeftAlt
#define BM_KEY_LEFT_SUPER      ::GUI::Key::LeftSuper
#define BM_KEY_RIGHT_SHIFT     ::GUI::Key::RightShift
#define BM_KEY_RIGHT_CONTROL   ::GUI::Key::RightControl
#define BM_KEY_RIGHT_ALT       ::GUI::Key::RightAlt
#define BM_KEY_RIGHT_SUPER     ::GUI::Key::RightSuper
#define BM_KEY_MENU            ::GUI::Key::Menu