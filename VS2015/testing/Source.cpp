#include "Game/Window.h"
#include "Math/Vector.h"
#include "Graphics/Mesh.h"


#include "Core\AssetManager.h"

// @Note: Not sure why the sample project has to include the engine dependencies in order to work. 
// Need to make it so that is not the case.

// @Note: Have to figure out how to deal with sdl defining the "main" macro. Find a solution for this
// instead of making sure that the user has to undef main every time. Could place the undef in the window
// class for now if I cant find a fix for it.

#undef main;
using namespace edn;

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


int main()
{
	WindowConfiguration window_config={
		"Title",
		600, 400,
		200, 200,
		EDN_WINDOW_VSYNC | EDN_WINDOW_HIDE_CURSOR
	};

	std::cout << sizeof(SDL_Scancode) << std::endl;

	Window & window = Window::Instance();
	window.Initialize();
	window.SetClearColor(0x282828);

	AssetManager::SetAssetPath(os::MakePath(os::ExecDir(), "Assets"));
	AssetManager::SetCachePath(os::MakePath(os::ExecDir(), "Cached"));

	AssetManager::Register<TestAsset>();
	AssetManager::Register<Mesh>();

	String filename = "testing.txt";
	//TestAsset * asset = AssetManager::Load<TestAsset>(filename);

	filename = "BigBoy.obj";
	Mesh * mesh = AssetManager::Load<Mesh>(filename);

	//std::cout << asset->Text() << std::endl;

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