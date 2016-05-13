#include "Precompiled.h"
#include "Input.h"

#include "SDL2\SDL.h"
#include "Window.h"

namespace edn
{
	//
	// InputHandle
	//
	bool Input::KeyPress(KeyCode code)
	{
		return m_keyboardState.KeyPress(code);
	}
	bool Input::KeySinglePress(KeyCode code)
	{
		return m_keyboardState.KeySinglePress(code);
	}
	bool Input::KeyRelease(KeyCode code)
	{
		return m_keyboardState.KeyRelease(code);
	}

	bool Input::MouseButtonPress(MouseButton button)
	{
		return m_mouseState.ButtonPress(button);
	}
	bool Input::MouseButtonSinglePress(MouseButton button)
	{
		return m_mouseState.ButtonSinglePress(button);
	}
	bool Input::MouseButtonRelease(MouseButton button)
	{
		return m_mouseState.ButtonRelease(button);
	}
	s32 Input::MouseX()
	{
		return m_mouseState.MouseX();
	}
	s32 Input::MouseY()
	{
		return m_mouseState.MouseY();
	}
	s32 Input::MouseDeltaX()
	{
		return m_mouseState.DeltaX();
	}
	s32 Input::MouseDeltaY()
	{
		return m_mouseState.DeltaY();
	}
	s32 Input::MouseWheelX()
	{
		return m_mouseState.MouseWheelX();
	}
	s32 Input::MouseWheelY()
	{
		return m_mouseState.MouseWheelY();
	}

	bool Input::ConnectedController(s32 controller)
	{
		return m_controllerState.Connected(controller);
	}
	bool Input::ContollerButtonPress(ControllerButton button, s32 controller)
	{
		return m_controllerState.ButtonPress(button, controller);
	}
	bool Input::ContollerButtonSinglePress(ControllerButton button, s32 controller)
	{
		return m_controllerState.ButtonSinglePress(button, controller);
	}
	bool Input::ContollerButtonRelease(ControllerButton button, s32 controller)
	{
		return m_controllerState.ButtonRelease(button, controller);
	}
	float Input::ControllerGetAxis(ControllerAxis axis, s32 controller)
	{
		return m_controllerState.Axis(axis, controller);
	}

	void Input::Update()
	{
		m_keyboardState.updatePrev();
		m_mouseState.updatePrev();
		m_controllerState.updatePrev();
	}

	void Input::SDLEventHandle(SDL_Event e)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			m_keyboardState.keyDown(e.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			m_keyboardState.keyUp(e.key.keysym.scancode);
			break;
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			m_mouseState.mouseEvent(e.button);
			break;
		case SDL_MOUSEWHEEL:
			m_mouseState.mouseWheelEvent(e.wheel);
			break;
		case SDL_MOUSEMOTION:
			m_mouseState.moveMouse(e.motion.x, e.motion.y);
			break;
		case SDL_CONTROLLERDEVICEADDED:
		{
			for (u8 i = 0; i < 4; ++i)
			{
				if (!m_controllerState.Connected(i))
				{
					m_controllerState.m_controllers[i] = SDL_GameControllerOpen(e.cdevice.which);
					m_controllerState.m_controllerIndices[i] = SDL_JoystickID(SDL_GameControllerGetJoystick(m_controllerState.m_controllers[i]));
					m_controllerState.connected(true, i);
				}
			}
		}break;
		case SDL_CONTROLLERDEVICEREMOVED:
		{
			int index = m_controllerState.getPlayerFromControllerIndex(e.cdevice.which);
			SDL_GameControllerClose(m_controllerState.m_controllers[index]);
			m_controllerState.connected(false, index);
			m_controllerState.m_controllerIndices[index] = -1;
		}break;

		case SDL_CONTROLLERBUTTONDOWN:
			m_controllerState.buttonDown((SDL_GameControllerButton)e.cbutton.button, m_controllerState.getPlayerFromControllerIndex(e.cdevice.which));
			break;
		case SDL_CONTROLLERBUTTONUP:
			m_controllerState.buttonUp((SDL_GameControllerButton)e.cbutton.button, m_controllerState.getPlayerFromControllerIndex(e.cdevice.which));
			break;
		case SDL_CONTROLLERAXISMOTION:
			m_controllerState.axis((SDL_GameControllerAxis)e.caxis.axis, e.caxis.value, m_controllerState.getPlayerFromControllerIndex(e.cdevice.which));
			break;
		}
	}

	//
	// Keyboard Implementation
	//
	KeyboardState::KeyboardState()
	{

	}

	KeyboardState::~KeyboardState()
	{

	}

	bool KeyboardState::KeyPress(KeyCode key)
	{
		SDL_Scancode code = convertFromKeyCode(key);
		return m_current[code];
	}

	bool KeyboardState::KeyRelease(KeyCode key)
	{
		SDL_Scancode code = convertFromKeyCode(key);
		return !m_current[code] && m_preveous[code];
	}

	bool KeyboardState::KeySinglePress(KeyCode key)
	{
		SDL_Scancode code = convertFromKeyCode(key);
		return m_current[code] && !m_preveous[code];
	}

	void KeyboardState::keyDown(SDL_Scancode code)
	{
		m_current[code] = true;
	}

	void KeyboardState::keyUp(SDL_Scancode code)
	{
		m_current[code] = false;
	}

	void KeyboardState::updatePrev()
	{
		m_preveous = m_current;
	}

	SDL_Scancode KeyboardState::convertFromKeyCode(KeyCode key)
	{
		switch (key)
		{
		case KeyCode::KEY_A:
			return SDL_SCANCODE_A;
		case KeyCode::KEY_B:
			return SDL_SCANCODE_B;
		case KeyCode::KEY_C:
			return SDL_SCANCODE_C;
		case KeyCode::KEY_D:
			return SDL_SCANCODE_D;
		case KeyCode::KEY_E:
			return SDL_SCANCODE_E;
		case KeyCode::KEY_F:
			return SDL_SCANCODE_F;
		case KeyCode::KEY_G:
			return SDL_SCANCODE_G;
		case KeyCode::KEY_H:
			return SDL_SCANCODE_H;
		case KeyCode::KEY_I:
			return SDL_SCANCODE_I;
		case KeyCode::KEY_J:
			return SDL_SCANCODE_J;
		case KeyCode::KEY_K:
			return SDL_SCANCODE_K;
		case KeyCode::KEY_L:
			return SDL_SCANCODE_L;
		case KeyCode::KEY_M:
			return SDL_SCANCODE_M;
		case KeyCode::KEY_N:
			return SDL_SCANCODE_N;
		case KeyCode::KEY_O:
			return SDL_SCANCODE_O;
		case KeyCode::KEY_P:
			return SDL_SCANCODE_P;
		case KeyCode::KEY_Q:
			return SDL_SCANCODE_Q;
		case KeyCode::KEY_R:
			return SDL_SCANCODE_R;
		case KeyCode::KEY_S:
			return SDL_SCANCODE_S;
		case KeyCode::KEY_T:
			return SDL_SCANCODE_T;
		case KeyCode::KEY_U:
			return SDL_SCANCODE_U;
		case KeyCode::KEY_V:
			return SDL_SCANCODE_V;
		case KeyCode::KEY_W:
			return SDL_SCANCODE_W;
		case KeyCode::KEY_X:
			return SDL_SCANCODE_X;
		case KeyCode::KEY_Y:
			return SDL_SCANCODE_Y;
		case KeyCode::KEY_Z:
			return SDL_SCANCODE_Z;
		
		case KeyCode::KEY_F1:
			return SDL_SCANCODE_F1;
		case KeyCode::KEY_F2:
			return SDL_SCANCODE_F2;
		case KeyCode::KEY_F3:
			return SDL_SCANCODE_F3;
		case KeyCode::KEY_F4:
			return SDL_SCANCODE_F4;
		case KeyCode::KEY_F5:
			return SDL_SCANCODE_F5;
		case KeyCode::KEY_F6:
			return SDL_SCANCODE_F6;
		case KeyCode::KEY_F7:
			return SDL_SCANCODE_F7;
		case KeyCode::KEY_F8:
			return SDL_SCANCODE_F8;
		case KeyCode::KEY_F9:
			return SDL_SCANCODE_F9;
		case KeyCode::KEY_F10:
			return SDL_SCANCODE_F10;
		case KeyCode::KEY_F11:
			return SDL_SCANCODE_F11;
		case KeyCode::KEY_F12:
			return SDL_SCANCODE_F12;

		case KeyCode::KEY_NUM0:
			return SDL_SCANCODE_0;
		case KeyCode::KEY_NUM1:
			return SDL_SCANCODE_1;
		case KeyCode::KEY_NUM2:
			return SDL_SCANCODE_2;
		case KeyCode::KEY_NUM3:
			return SDL_SCANCODE_3;
		case KeyCode::KEY_NUM4:
			return SDL_SCANCODE_4;
		case KeyCode::KEY_NUM5:
			return SDL_SCANCODE_5;
		case KeyCode::KEY_NUM6:
			return SDL_SCANCODE_6;
		case KeyCode::KEY_NUM7:
			return SDL_SCANCODE_7;
		case KeyCode::KEY_NUM8:
			return SDL_SCANCODE_8;
		case KeyCode::KEY_NUM9:
			return SDL_SCANCODE_9;

		
		case KeyCode::KEY_LEFT:
			return SDL_SCANCODE_LEFT;
		case KeyCode::KEY_RIGHT:
			return SDL_SCANCODE_RIGHT;
		case KeyCode::KEY_UP:
			return SDL_SCANCODE_UP;
		case KeyCode::KEY_DOWN:
			return SDL_SCANCODE_DOWN;
		case KeyCode::KEY_SPACE:
			return SDL_SCANCODE_SPACE;
		
		case KeyCode::KEY_ESC:
			return SDL_SCANCODE_ESCAPE;
		case KeyCode::KEY_RETURN:
			return SDL_SCANCODE_RETURN;
		case KeyCode::KEY_BACKSLASH:
			return SDL_SCANCODE_BACKSLASH;
		case KeyCode::KEY_TAB:
			return SDL_SCANCODE_TAB;
		case KeyCode::KEY_FORWARD_SLASH:
			return SDL_SCANCODE_SLASH;
		case KeyCode::KEY_PERIOD:
			return SDL_SCANCODE_PERIOD;
		case KeyCode::KEY_COMMA:
			return SDL_SCANCODE_COMMA;
		case KeyCode::KEY_DEL:
			return SDL_SCANCODE_DELETE;

		case KeyCode::KEY_SHIFT:
			return SDL_SCANCODE_LSHIFT;
		case KeyCode::KEY_CTRL:
			return SDL_SCANCODE_LCTRL;
		case KeyCode::KEY_ALT:
			return SDL_SCANCODE_LALT;
		default:
			return SDL_SCANCODE_0;
			break;
		}
	}

	//
	// Mouse
	//
	MouseState::MouseState()
	{
		m_position     = { 0,0 };
		m_prevPosition = { 0,0 };
		m_wheel         = { 0,0 };
		m_prevWeel     = { 0,0 };

		m_current[mouseButtonToIndex(MouseButton::MOUSE_BUTTON_LEFT)].state   = SDL_RELEASED;
		m_current[mouseButtonToIndex(MouseButton::MOUSE_BUTTON_RIGHT)].state  = SDL_RELEASED;
		m_current[mouseButtonToIndex(MouseButton::MOUSE_BUTTON_MIDDLE)].state = SDL_RELEASED;

		m_preveous[mouseButtonToIndex(MouseButton::MOUSE_BUTTON_LEFT)].state = SDL_RELEASED;
		m_preveous[mouseButtonToIndex(MouseButton::MOUSE_BUTTON_RIGHT)].state = SDL_RELEASED;
		m_preveous[mouseButtonToIndex(MouseButton::MOUSE_BUTTON_MIDDLE)].state = SDL_RELEASED;

	}

	MouseState::~MouseState()
	{

	}

	bool MouseState::ButtonPress(MouseButton button)
	{
		return m_current[mouseButtonToIndex(button)].state == SDL_PRESSED;
	}

	bool MouseState::ButtonRelease(MouseButton button)
	{
		const s32 index = mouseButtonToIndex(button);
		return m_current[index].state == SDL_RELEASED &&
			m_preveous[index].state == SDL_PRESSED;
	}

	bool MouseState::ButtonSinglePress(MouseButton button)
	{
		const s32 index = mouseButtonToIndex(button);
		return m_current[index].state == SDL_PRESSED &&
			m_preveous[index].state == SDL_RELEASED;
	}

	s32 MouseState::DeltaX()
	{
		if (m_position.x != m_prevPosition.x)
			return m_position.x - m_prevPosition.x;
		return 0;
	}

	s32 MouseState::DeltaY()
	{
		if (m_position.y != m_prevPosition.y)
			return m_position.y - m_prevPosition.y;
		return 0;
	}

	void MouseState::moveMouse(s32 x, s32 y)
	{
		m_position = { x, y };
	}

	void MouseState::mouseEvent(SDL_MouseButtonEvent e)
	{
		switch (e.button)
		{
			case SDL_BUTTON_LEFT:
				m_current[0].state  = e.state;
				m_current[0].clicks = e.clicks;
				break;

			case SDL_BUTTON_RIGHT:
				m_current[1].state  = e.state;
				m_current[1].clicks = e.clicks;
				break;

			case SDL_BUTTON_MIDDLE:
				m_current[2].state = e.state;
				m_current[2].clicks = e.clicks;
				break;
		}
	}

	void MouseState::mouseWheelEvent(SDL_MouseWheelEvent e)
	{
		m_wheel = { e.x, e.y };
	}

	void MouseState::updatePrev()
	{
		m_prevPosition = m_position;
		m_prevWeel = m_wheel;
		m_wheel.y = 0;
		memcpy(m_preveous, m_current, sizeof(m_current));
	}

	s32 MouseState::mouseButtonToIndex(MouseButton button)
	{
		switch (button)
		{
			case MouseButton::MOUSE_BUTTON_LEFT:   return 0;
			case MouseButton::MOUSE_BUTTON_RIGHT:  return 1;
			case MouseButton::MOUSE_BUTTON_MIDDLE: return 2;
		}
		return 0;
	}

	//
	// Controllers
	//

	ControllerState::ControllerState()
	{
		for (u8 i = 0; i < 4; ++i)
		{
			m_currentController[i][SDL_CONTROLLER_BUTTON_DPAD_UP] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_DPAD_DOWN] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_DPAD_LEFT] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_A] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_B] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_X] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_Y] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_LEFTSHOULDER] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_LEFTSTICK] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_RIGHTSTICK] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_START] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_BACK] = false;
			m_currentController[i][SDL_CONTROLLER_BUTTON_INVALID] = false;

			m_currentAxis[i][SDL_CONTROLLER_AXIS_LEFTX] = false;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_LEFTY] = false;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_RIGHTX] = false;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_RIGHTY] = false;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_TRIGGERLEFT] = false;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_TRIGGERRIGHT] = false;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_INVALID] = false;
		}
	}
	
	ControllerState::~ControllerState()
	{
		//ClearContainer(m_currentAxis);
		//ClearContainer(m_currentController);
		//ClearContainer(m_previousController);
	}

	bool ControllerState::Connected(s32 controller)
	{
		if (controller >= 4) return false;
		return m_currentControllerStatus[controller];
	}

	bool ControllerState::ButtonPress(ControllerButton button, s32 controller)
	{
		if (controller >= 4) return false;
		SDL_GameControllerButton code = convertFromControllerButton(button);
		return m_currentController[controller][code];
	}

	bool ControllerState::ButtonRelease(ControllerButton button, s32 controller)
	{
		if (controller >= 4) return false;
		SDL_GameControllerButton code = convertFromControllerButton(button);
		return !m_currentController[controller][code] &&
			m_previousController[controller][code];
	}

	bool ControllerState::ButtonSinglePress(ControllerButton button, s32 controller)
	{
		if (controller >= 4) return false;
		SDL_GameControllerButton code = convertFromControllerButton(button);
		return m_currentController[controller][code] &&
			!m_previousController[controller][code];
	}

	f32 ControllerState::Axis(ControllerAxis axis, s32 controller)
	{
		if (controller >= 4) return 0.0f;
		SDL_GameControllerAxis code = convertFromControllerAxis(axis);
		return (f32)m_currentAxis[controller][code];
	}

	void ControllerState::updatePrev()
	{
		for (int i = 0; i < 4; i++)
			m_previousController[i] = m_currentController[i];
	}

	void ControllerState::connected(bool status, s32 controller)
	{
		if (controller > 3) return;
		m_currentControllerStatus[controller] = status;
	}

	void ControllerState::axis(SDL_GameControllerAxis axis, s16 value, s32 controller)
	{
		if (controller > 3) return;
		m_currentAxis[controller][axis] = value;
	}

	void ControllerState::buttonDown(SDL_GameControllerButton button, s32 controller)
	{
		if (controller > 3) return;
		m_currentController[controller][button] = true;
	}

	void ControllerState::buttonUp(SDL_GameControllerButton button, s32 controller)
	{
		if (controller > 3) return;
		m_currentController[controller][button] = false;
	}

	s32 ControllerState::getPlayerFromControllerIndex(s32 index)
	{
		for (int i = 0; i < 4; ++i)
			if (m_controllerIndices[i] == index)
				return i;
		return 0;
	}

	SDL_GameControllerButton ControllerState::convertFromControllerButton(ControllerButton button)
	{
		switch (button)
		{
		case ControllerButton::CONTROLLER_BUTTON_UP:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP;
		case ControllerButton::CONTROLLER_BUTTON_DOWN:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN;
		case ControllerButton::CONTROLLER_BUTTON_LEFT:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT;
		case ControllerButton::CONTROLLER_BUTTON_RIGHT:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
		case ControllerButton::CONTROLLER_BUTTON_A:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A;
		case ControllerButton::CONTROLLER_BUTTON_B:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B;
		case ControllerButton::CONTROLLER_BUTTON_X:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X;
		case ControllerButton::CONTROLLER_BUTTON_Y:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y;
		case ControllerButton::CONTROLLER_BUTTON_LEFTBUMPER:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
		case ControllerButton::CONTROLLER_BUTTON_RIGHTBUMPER:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		case ControllerButton::CONTROLLER_BUTTON_LEFTSTICK:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSTICK;
		case ControllerButton::CONTROLLER_BUTTON_RIGHTSTICK:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSTICK;
		case ControllerButton::CONTROLLER_BUTTON_START:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START;
		case ControllerButton::CONTROLLER_BUTTON_BACK:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK;
		}
	}

	SDL_GameControllerAxis ControllerState::convertFromControllerAxis(ControllerAxis axis)
	{
		switch (axis)
		{
		case ControllerAxis::CONTROLLER_AXIS_LEFTX:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;
		case ControllerAxis::CONTROLLER_AXIS_LEFTY:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;
		case ControllerAxis::CONTROLLER_AXIS_RIGHTX:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX;
		case ControllerAxis::CONTROLLER_AXIS_RIGHTY:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY;
		case ControllerAxis::CONTROLLER_AXIS_LEFTTRIGGER:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT;
		case ControllerAxis::CONTROLLER_AXIS_RIGHTTRIGGER:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
		}
	}
}