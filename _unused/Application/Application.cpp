#include "Precompiled.h"
#include "Application.h"

namespace edn
{
	Application app;

	Application::Application(const WindowCreateInfo& info)
	{
		initialize(info);
	}

	void Application::initialize(const WindowCreateInfo& info)
	{
		window.initialize(info);
	}

	Application::~Application()
	{
		cleanup();
	}

	void Application::cleanup()
	{
		window.cleanup();
	}

	void Application::update()
	{
		window.update();
	}
}