#pragma once

#include "../../Core/Platform.h"
#include "../../Core/Types.h"
#include "../WindowStyles.h"

namespace edn
{
	namespace Win32
	{
		struct WindowCreateInfo
		{
			static WindowCreateInfo Default;
			String title;
			u32 width;
			u32 height;
			u32 flags;
		};

		class Window
		{
		public:
			Window() = default;
			Window(const WindowCreateInfo& info);
			~Window();

			void initialize(const WindowCreateInfo& info = WindowCreateInfo::Default);
			void cleanup();

			void update();
			void setWindowStyle(WindowStyle style);

			bool isRunning() { return running; }
			void setRunning(bool running) { this->running = running; }

			void show();

			HWND getHwnd() { return hwnd; }
			HINSTANCE getHInstance() { return hinstance; }

		private:
			void change_style();

		private:
			String title = "EDEN Engine";
			u32 width = 800;
			u32 height = 600;
			bool running = false;
			bool initialized = false;
			bool fullscreen = false;
			bool borderless = false;
			WindowStyle style = WindowStyle::WINDOWED;

			// Windows
			HINSTANCE hinstance = 0;
			HWND hwnd = 0;
			String class_name = "";
		};
	}
}
