#include "Application/Application.h"
#include "Core/Logging.h"

// @Note: Not sure why the sample project has to include the engine dependencies in order to work. 
// @Todo: Need to make it so that is not the case.

using namespace edn;
using namespace std;

int engine()
{
	App.createWindow();

	while (App.running)
	{
		App.window.processOsEvents();
	}

	App.shutdown();
	return 0;
}

int main(int argc, char** argv)
{
	Logging::init(argc, argv);
	return engine();
}