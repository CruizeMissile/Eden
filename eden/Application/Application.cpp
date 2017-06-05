#include "Precompiled.h"
#include "Application.h"

namespace edn
{
	void Application::createWindow(const WindowInfo& info)
	{ 
		window.createWindow(info);
		running = true;
	}

	void Application::update()
	{
		window.processOsEvents();
		running = window.checkRunningStatus();
	}

	//vec3 Application::getCursorPosition()
	//{
	//	return window.getCursorPosition();
	//}

	void Application::setCursorPosition(s32 x, s32 y)
	{
		window.setCursorPosition(x, y);
	}
}