#pragma once
#include "Application/WindowInfo.h"
#include "Core/Platform.h"

namespace edn
{
	namespace win32
	{
		class Window
		{
		public:
			Window();
			~Window();

			void createWindow(const WindowInfo& create_info = WindowInfo::Default);

			u32 getWidth() { return width; }
			u32 getHeight() { return height; }

			bool setFullscreen(bool fullscreen);
			bool setBordered(bool bordered);
			bool setResizable(bool bordered);

			HWND getHwnd() { return hwnd; }
			HINSTANCE getHInstance() { return hinstance; }

			void processOsEvents();

		private:
			static LRESULT CALLBACK WindowsEventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

			String title;
			u32 width;
			u32 height;

			bool fullscreen = false;
			bool bordered = true;
			bool resizable = true;

			// Widnows specific
			HWND hwnd = 0;
			HINSTANCE hinstance = 0;
			String class_name = "";
		};
	}
}