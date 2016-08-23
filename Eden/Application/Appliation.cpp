#include "Precompiled.h"
#include "Application/Application.h"

namespace edn
{
	const ApplicationConfiguration ApplicationConfiguration::Default = 
	{
		"EDEN ENGINE", 1280, 720, 0
	};

	Application::Application()
		: title(ApplicationConfiguration::Default.title)
		, width(ApplicationConfiguration::Default.width)
		, height(ApplicationConfiguration::Default.height)
		, flags(ApplicationConfiguration::Default.flags)
		, style(WindowStyle::EDN_WINDOW_WINDOWED)
		, prev_style(style)
	{
		setupOsWindow();
		running = true;
	}

	Application::Application(const ApplicationConfiguration & config)
		: title(config.title)
		, width(config.width)
		, height(config.height)
		, flags(config.flags)
		, style(WindowStyle::EDN_WINDOW_WINDOWED)
		, prev_style(style)
	{
		setupOsWindow();
		running = true;
	}

	Application::~Application()
	{
		cleanupOsWindow();
	}

	void Application::update()
	{
		updateOsWindow();
	}

	void Application::close()
	{
		running = false;
	}

	void Application::setWindowStyle(WindowStyle s)
	{
		// If the style is the current style then dont have to update
		if (style == s)
			return;
		style = s;
		updateOsWindowStyle();
		prev_style = style;
	}
}
