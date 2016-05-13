#include "Game\Window.h"

// @Note: Not sure why the sample project has to include the engine dependencies in order to work. 
// Need to make it so that is not the case.

// @Note: Have to figure out how to deal with sdl defining the "main" macro. Find a solution for this
// instead of making sure that the user has to undef main every time. Could place the undef in the window
// class for now if I cant find a fix for it.

#undef main;
using namespace edn;

int main()
{
	WindowConfiguration window_config={
		"Title",
		600, 400,
		200, 200,
		EDN_WINDOW_VSYNC | EDN_WINDOW_HIDE_CURSOR
	};

	Window & window = Window::Instance();
	window.Initialize(window_config);
	window.SetClearColor(0x282828);

	while (window.IsRunning())
	{
		window.PollEvents();
		window.Update();
		window.Clear();

		window.SwapBuffers();
	}
	window.Cleanup();
	return 0;
}