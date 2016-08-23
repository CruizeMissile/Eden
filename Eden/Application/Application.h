#pragma once
#include "Core/Platform.h"
#include "Core/Types.h"
#include "vulkan/vulkan.h"

namespace edn
{
	enum class WindowStyle
	{
		EDN_WINDOW_FULLSCREEN,
		EDN_WINDOW_BORDERLESS,
		EDN_WINDOW_WINDOWED,
		EDN_WINDOW_WINDOWED_FIXED,
		EDN_WINDOW_BORDERLESS_WINDOW,
	};

	enum class ApplicationFlags
	{
		EDN_WINDOW_RUNNING = 1,
		EDN_WINDOW_VSYNC = 1 << 1,
	};

	typedef struct ApplicationConfiguration
	{
		static const ApplicationConfiguration Default;

		String title;
		u32 width, height;

		u32 flags;
	};


	class Application
	{
	public:
		Application();
		Application(const ApplicationConfiguration & config);
		~Application();

		void update();
		void close();

		bool isRunning() { return running; }
		WindowStyle getStyle() { return style; }

		void setWindowStyle(WindowStyle style);

	private:

		void updateOsWindowStyle();

		void setupOsWindow();
		void cleanupOsWindow();

		void updateOsWindow();
		void setupSurface();


		std::string title;
		WindowStyle style, prev_style;

		u32 width, height;
		u32 flags;
		bool running = false;

#if defined EDN_WINDOWS
		HINSTANCE hinstance;
		HWND hwnd;
		String classname;
#endif
	};
}