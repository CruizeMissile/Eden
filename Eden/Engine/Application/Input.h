#pragma once
#include "Application/Event.h"
#include "Core/Singleton.h"
#include "Core/Types.h"
#include "Math/Vector.h"

namespace edn
{
	enum class Key
	{
		Unknown = -1,
		Space = 32,
		Apostrophe = 39,
		Comma = 44, Minus, Period, Slash,
		Key0 = 48, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9,
		A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		LeftBracket, Backslash, RightBracket,
		Grave = 96,
		Semicolen = 59,
		Equals = 61,
		Escape = 256, Enter, Tab, Backspace, Insert, Delete, Right, Left, Down, Up, Pageup, Pagedown, Home, End,
		CapsLock = 280, ScrollLock, NumLock, PrintScreen, Pause,
		F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
		Kp0, Kp1, Kp2, Kp3, Kp4, Kp5, Kp6, Kp7, Kp8, Kp9,
		KpDecimal, KpDivide, KpMultiply, KpSubtract, KpAdd, KpEnter, KpEqual,
		LeftShift = 340, LeftContorl, LeftAlt, LeftSuper,
		RightShift, RightControl, RightAlt, RightSuper,
		Menu,
		NUM_KEYS
	};

	enum class MouseButton
	{
		Unknown = -1,
		Left = 0,
		Right,
		Middle,
		Button1 = 0,
		Button2,
		Button3,
		Button4,
		Button5,
		Button6,
		Button7,
		Button8,
		NUM_BUTTONS
	};

	static class Input : public Singleton<class Input>
	{
		friend class Application;
	public:
		bool isDown(const Key key) const;
		bool isUp(const Key key) const;

		bool isDown(const MouseButton button) const;
		bool isUp(const MouseButton button) const;

		void setKeyState(const Key key, bool state) { keys[static_cast<u32>(key)] = state; }
		void setMouseBtnState(const MouseButton btn, bool state) { keys[static_cast<u32>(btn)] = state; }

		void updateCursorPosition(s32 x, s32 y);

	private:
		void update();

		bool keys[static_cast<u32>(Key::NUM_KEYS)] = { false };
		s32 x = 0;
		s32 y = 0;
	} &Input = Singleton<class Input>::instanceRef;


	namespace evn
	{
		struct KeyDown : public Event<KeyDown>
		{
			KeyDown(const Key key) : key(key) {}
			Key key;
		};

		struct KeyUp : public Event<KeyUp>
		{
			KeyUp(const Key key) : key(key) {}
			Key key;
		};

		struct MouseButtonDown : public Event<MouseButtonDown>
		{
			MouseButtonDown(const Key button) : button(button) {}
			Key button;
		};

		struct MouseButtonUp : public Event<MouseButtonUp>
		{
			MouseButtonUp(const Key button) : button(button) {}
			Key button;
		};

		struct MouseMovement : public Event<MouseMovement>
		{
			MouseMovement(const u32 x, const u32 y) : x(x), y(y) {}
			u32 x, y;
		};
	}

}
