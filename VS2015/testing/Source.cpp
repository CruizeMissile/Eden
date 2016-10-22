#include "Math/Vector.h"
#include "Core/Common.h"
#include "Entity/Component.h"

#include "Core\AssetManager.h"
#include "Application/Application.h"

// @Note: Not sure why the sample project has to include the engine dependencies in order to work. 
// @Todo: Need to make it so that is not the case.

// @Note: Have to figure out how to deal with sdl defining the "main" macro. Find a solution for this
// instead of making sure that the user has to undef main every time. Could place the undef in the window
// class for now if I cant find a fix for it.

using namespace edn;
using namespace std;

class TestAsset : public Asset
{
public:
	TestAsset()
	{
		m_subDir = "Testing";
	}

	String Text() { return m_text; }

	virtual void loadFromFile(String filename) override
	{
		m_text = GetTextFileContent(filename);
	}

	virtual void loadFromCashe(String filename) override
	{

	}

	virtual void writeCacheFile(String filename) override
	{

	}
private:
	String m_text;
};

int engine()
{
	app.initialize();
	while (app.isRunning())
	{
		app.update();
	}
	app.cleanup();

	return 0;
}

int main()
{
	return engine();
}