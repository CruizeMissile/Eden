#pragma once
#include "Core/Platform.h"
#include "Core/Singleton.h"
#include "Core/Types.h"

#if defined(EDN_WINDOWS)
#include "Application/Win32/Window.h"
#elif defined(EDN_LINUX)
#include "Application/Linux/Window.h"
#endif

namespace edn
{
#if defined(EDN_WINDOWS)
	using Window = win32::Window;
#elif defined(EDN_LINUX)
	using Window = linux::Window;
#else
#error Not Implemented
#endif

	static class Application : public Singleton<class Application>
	{
		friend Window;
	public:
		Application() {}
		~Application() {}

		void createWindow(const WindowInfo& info = WindowInfo::Default);
		void shutdown() { running = false; }

		bool running;
		Window window;
	private:
	} &App = Singleton<class Application>::instanceRef;
}
