#pragma once
#include "Core/Platform.h"
#include "Core/Singleton.h"
#include "Core/Types.h"

#if defined(EDN_WINDOWS)
#include "Application/Win32/Win32-Window.h"
#endif

namespace edn
{
#if defined(EDN_WINDOWS)
	using Window = win32::Window;
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