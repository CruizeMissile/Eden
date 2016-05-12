#include "Game\Window.h"

#undef main;5

int main()
{
	edn::Window window;
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