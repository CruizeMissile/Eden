#include "Precompiled.h"
#include "Application/Application.h"

namespace edn
{
#if 0
	const ApplicationConfiguration ApplicationConfiguration::Default = 
	{
		"EDEN ENGINE", 1280, 720, 0
	};

	Application::Application()
		: title(ApplicationConfiguration::Default.title)
		, size(Size{ ApplicationConfiguration::Default.width, ApplicationConfiguration::Default.height })
		, flags(ApplicationConfiguration::Default.flags)
		, style(WindowStyle::EDN_WINDOW_WINDOWED)
		, prev_style(style)
	{
		setupOsWindow();
		running = true;
	}

	Application::Application(const ApplicationConfiguration & config)
		: title(config.title)
		, size(Size{config.width, config.height})
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
#endif
}
