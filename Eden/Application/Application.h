#include "../Core/Platform.h"
#include "../Core/Types.h"
#include "WindowStyles.h"

#if defined(EDN_WINDOWS)
	#include "Windows/Window.h"
#endif

namespace edn
{
#if defined(EDN_WINDOWS)
	using Window = Win32::Window;
	using WindowCreateInfo = Win32::WindowCreateInfo;
#endif

	class Application
	{
	public:
		Application() = default;
		Application(const WindowCreateInfo& info);
		~Application();

		void initialize(const WindowCreateInfo& info = WindowCreateInfo::Default);
		void cleanup();

		void run();
		void update();
		
		void setWindowStyle(WindowStyle style);

		bool isRunning() { return window.isRunning(); }

	private:
		Window window;
	};
	extern Application app;
}