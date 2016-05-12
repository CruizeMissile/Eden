#include "Game\Window.h"

#undef main;
using namespace edn;

int main()
{
	Window & window = Window::Instance();
	window.Initialize();
	window.SetClearColor(0x282828);

	while (window.IsRunning())
	{
		window.PollEvents();
		window.Clear();

		window.SwapBuffers();
	}
	window.Cleanup();
	return 0;
}