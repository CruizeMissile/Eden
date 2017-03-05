#pragma once
#include "Application/WindowInfo.h"

namespace edn
{
	namespace linux
	{
		class Window
		{
		public:
			Window(){}
			~Window(){}

			void createWindow(const WindowInfo& create_info = WindowInfo::Default){}

			u32 getWidth() { return width; }
			u32 getHeight() { return height; }

			bool setFullscreen(bool fullscreen){return true;}
			bool setBordered(bool bordered){return true;}
			bool setResizable(bool bordered){return true;}

			void processOsEvents() {}

		private:
			String title;
			u32 width;
			u32 height;

			bool fullscreen = false;
			bool bordered = true;
			bool resizeable = true;
		};
	}
}
