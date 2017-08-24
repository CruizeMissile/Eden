#pragma once
#include "Application/Window.h"
#include "Core/Platform.h"
#include "Core/Singleton.h"
#include "Core/Types.h"


namespace edn
{
	static class Application : public Singleton<class Application>
	{
	public:
		Application() {}
		~Application() {}

		void createWindow(const WindowInfo& info = WindowInfo::Default);
		void update();
		void shutdown() { running = false; }

		bool running;
		Window window;
	private:
	} &App = Singleton<class Application>::instanceRef;
}
