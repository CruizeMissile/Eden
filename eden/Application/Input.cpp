#include "Precompiled.h"
#include "Application/Application.h"
#include "Application/Input.h"

namespace edn
{
	bool Input::isDown(const Key key) const
	{
		return keys[static_cast<u32>(key)];
	}

	bool Input::isUp(const Key key) const
	{
		return !isDown(key);
	}

	bool Input::isDown(const MouseButton button) const
	{
		return keys[static_cast<u32>(button)];
	}

	bool Input::isUp(const MouseButton button) const
	{
		return !isDown(button);
	}

	void Input::updateCursorPosition(u32 xpos, u32 ypos)
	{
		cursor_position.x = xpos;
		cursor_position.y = ypos;
	}

	void Input::setCursorPosition(u32 x, u32 y)
	{
		App.setCursorPosition(x, y);
	}

    cml::uvec2 Input::getCursorPosition() const
    {
        return cursor_position;
    }

	void Input::update()
	{

	}
}
