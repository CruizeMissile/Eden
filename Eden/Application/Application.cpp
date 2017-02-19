#include "Precompiled.h"
#include "Application.h"

namespace edn
{
	void Application::createWindow(const WindowInfo& info)
	{ 
		window.createWindow(info);
		running = true;
	}
}