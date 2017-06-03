#include "Application/Application.h"
#include "Application/Event.h"
#include "Application/Input.h"

// @Note: Not sure why the sample project has to include the engine dependencies in order to work.
// @Todo: Need to make it so that is not the case.

using namespace edn;
using namespace std;

struct Something
{
	Listener<evn::MouseMovement> on_mouse_move;
	Listener<evn::MouseButtonDown> on_mouse_down;
	Listener<evn::MouseButtonUp> on_mouse_up;
	Listener<evn::KeyDown> on_key_down;
	Listener<evn::KeyUp> on_key_up;
	Listener<evn::WindowEntered> on_window_enter;
	Listener<evn::WindowExit> on_window_exit;
};

int engine()
{
	App.createWindow();
	
	Something something;
	something.on_mouse_move.callback = [](auto& e) { cout << e.x << " : " << e.y << endl; };
	something.on_mouse_down.callback = [](auto& e) { cout << static_cast<u32>(e.button) << endl; };
	something.on_mouse_up.callback = [](auto& e) { cout << static_cast<u32>(e.button) << endl; };
	something.on_key_down.callback = [](auto& e) { cout << static_cast<u32>(e.key) << endl; };
	something.on_key_up.callback = [](auto& e) { cout << static_cast<u32>(e.key) << endl; };
	something.on_key_up.callback = [](auto& e) { cout << static_cast<u32>(e.key) << endl; };
	something.on_window_enter.callback = [](auto& e) { cout << "Entered" << endl; };
	something.on_window_exit.callback = [](auto& e) { cout << "Exit" << endl; };

	while (App.running)
	{
		App.update();
		EventQueue.dispatch();
	}

	App.shutdown();
	return 0;
}

int main(int argc, char** argv)
{
	return engine();
}
