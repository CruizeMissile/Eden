#ifndef H_GAME_INPUT_H
#define H_GAME_INPUT_H

#include "Precompiled.h"
#include <SDL2\SDL.h>

namespace edn
{
	//
	// Enum Definitions
	//
	typedef enum
	{
		MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_MIDDLE
	}MouseButton;

	typedef enum
	{
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_NUM1,
		KEY_NUM2,
		KEY_NUM3,
		KEY_NUM4,
		KEY_NUM5,
		KEY_NUM6,
		KEY_NUM7,
		KEY_NUM8,
		KEY_NUM9,
		KEY_NUM0,
		KEY_ESC,
		KEY_RETURN,
		KEY_SPACE,
		KEY_SHIFT,
		KEY_CTRL,
		KEY_ALT,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_FORWARD_SLASH,
		KEY_BACKSLASH,
		KEY_PERIOD,
		KEY_COMMA,
		KEY_DEL,
	}KeyCode;

	typedef enum 
	{
		CONTROLLER_BUTTON_UP,
		CONTROLLER_BUTTON_DOWN,
		CONTROLLER_BUTTON_LEFT,
		CONTROLLER_BUTTON_RIGHT,
		CONTROLLER_BUTTON_A,
		CONTROLLER_BUTTON_B,
		CONTROLLER_BUTTON_X,
		CONTROLLER_BUTTON_Y,
		CONTROLLER_BUTTON_LEFTBUMPER,
		CONTROLLER_BUTTON_RIGHTBUMPER,
		CONTROLLER_BUTTON_LEFTSTICK,
		CONTROLLER_BUTTON_RIGHTSTICK,
		CONTROLLER_BUTTON_START,
		CONTROLLER_BUTTON_BACK
	}ControllerButton;

	typedef enum 
	{
		CONTROLLER_AXIS_LEFTX,
		CONTROLLER_AXIS_LEFTY,
		CONTROLLER_AXIS_RIGHTX,
		CONTROLLER_AXIS_RIGHTY,
		CONTROLLER_AXIS_RIGHTTRIGGER,
		CONTROLLER_AXIS_LEFTTRIGGER
	}ControllerAxis;


	class KeyboardState;
	class MouseState;
	class ControllerState;

	//
	// Keyboard
	//
	class KeyboardState
	{
		typedef std::map<SDL_Scancode, bool> KeyState;
	
		friend class Input;

	public:
		KeyboardState();
		~KeyboardState();

		bool KeyPress(KeyCode key);
		bool KeyRelease(KeyCode key);
		bool KeySinglePress(KeyCode key);


	private:
		void updatePrev();
		void keyDown(SDL_Scancode code);
		void keyUp(SDL_Scancode code);
		SDL_Scancode convertFromKeyCode(KeyCode key);
	private:
		KeyState m_current;
		KeyState m_preveous;
	};


	//
	// Mouse
	//
	struct MouseClickedState
	{
		u8 clicks;
		u8 state;
	};

	class MouseState
	{
		static const u8 MOUSE_BUTTONS = 3;
		struct XY
		{
			s32 x, y;
		};

		friend class Input;

	public:
		MouseState();
		~MouseState();

		bool ButtonPress(MouseButton button);
		bool ButtonRelease(MouseButton button);
		bool ButtonSinglePress(MouseButton button);

		s32 MouseX() { return m_position.x; }
		s32 MouseY() { return m_position.y; }
		s32 MouseWheelX() { return m_wheel.x; }
		s32 MouseWheelY() { return m_wheel.y; }
		s32 DeltaX();
		s32 DeltaY();

	private:
		void moveMouse(s32 x, s32 y);
		void mouseEvent(SDL_MouseButtonEvent event);
		void mouseWheelEvent(SDL_MouseWheelEvent event);
		void updatePrev();
		s32 mouseButtonToIndex(MouseButton button);
	private:
		XY m_position;
		XY m_prevPosition;
		XY m_wheel;
		XY m_prevWeel;

		MouseClickedState m_current[MOUSE_BUTTONS];
		MouseClickedState m_preveous[MOUSE_BUTTONS];
	};

	//
	// Controller
	//
	class ControllerState
	{
		typedef std::map<SDL_GameControllerButton, bool> ControllerButtonState;
		typedef std::map<SDL_GameControllerAxis, s16> AxisState;

		friend class Input;

		const static u8 MAX_CONTROLLER_COUNT = 4;

	public:
		ControllerState();
		~ControllerState();

		bool Connected(s32 controller);
		bool ButtonPress(ControllerButton, s32 controller);
		bool ButtonSinglePress(ControllerButton, s32 controller);
		bool ButtonRelease(ControllerButton, s32 controller);
		f32 Axis(ControllerAxis axis, s32 controller);

	private:
		void updatePrev();
		void connected(bool status, s32 contorller);
		void axis(SDL_GameControllerAxis axis, s16 value, s32 controller);
		void buttonDown(SDL_GameControllerButton button, s32 controller);
		void buttonUp(SDL_GameControllerButton button, s32 controller);

		SDL_GameControllerButton convertFromControllerButton(ControllerButton button);
		SDL_GameControllerAxis convertFromControllerAxis(ControllerAxis axis);
		
		s32 getPlayerFromControllerIndex(s32 index);

	private:
		bool m_currentControllerStatus[MAX_CONTROLLER_COUNT];
		AxisState m_currentAxis[MAX_CONTROLLER_COUNT];
		ControllerButtonState m_currentController[MAX_CONTROLLER_COUNT];
		ControllerButtonState m_previousController[MAX_CONTROLLER_COUNT];
		SDL_GameController * m_controllers[MAX_CONTROLLER_COUNT];
		s32 m_controllerIndices[MAX_CONTROLLER_COUNT];
	};

	class Input : public Singleton<Input>
	{
	public:

		bool KeyPress(KeyCode code);
		bool KeySinglePress(KeyCode code);
		bool KeyRelease(KeyCode code);

		bool MouseButtonPress(MouseButton button);
		bool MouseButtonSinglePress(MouseButton button);
		bool MouseButtonRelease(MouseButton button);
		s32 MouseX();
		s32 MouseY();
		s32 MouseDeltaX();
		s32 MouseDeltaY();
		s32 MouseWheelX();
		s32 MouseWheelY();

		bool ConnectedController(s32 controller);
		bool ContollerButtonPress(ControllerButton button, s32 controller);
		bool ContollerButtonSinglePress(ControllerButton button, s32 controller);
		bool ContollerButtonRelease(ControllerButton button, s32 controller);
		float ControllerGetAxis(ControllerAxis axis, s32 controller);

		void Update();

		void SDLEventHandle(SDL_Event e);

	private:
		KeyboardState m_keyboardState;
		MouseState m_mouseState;
		ControllerState m_controllerState;
	};
}

#endif