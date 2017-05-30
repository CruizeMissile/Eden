#include "Precompiled.h"
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

	void Input::updateCursorPosition(s32 xpos, s32 ypos)
	{
		x = xpos;
		y = ypos;
	}

	void Input::update()
	{

	}
}