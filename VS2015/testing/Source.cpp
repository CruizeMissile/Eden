#include "Game\Window.h"

#undef main;
using namespace edn;

int main()
{
	WindowConfig window_config={
		"Title",
		1280, 720,
		0, 0,
		EDN_WINDOW_VSYNC | EDN_WINDOW_BOARDERLESS
	};

	Window & window = Window::Instance();
	window.Initialize();
	window.SetClearColor(0x282828);

	while (window.IsRunning())
	{
		window.Update();
		window.PollEvents();
		window.Clear();

		window.SwapBuffers();
	}
	window.Cleanup();
	return 0;
}