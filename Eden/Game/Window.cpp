#include "Precompiled.h"
#include "Window.h"
#include "Input.h"

namespace edn
{
	static bool configuration_passed = false;
	static WindowConfiguration default_configuration = {
		"Eden Engine",
		1280, 720,
		0, 0,
		0
	};

	Window::Window()
		: m_flags(0)
	{
	}

	Window::~Window()
	{
		Cleanup();
	}

	void Window::Cleanup()
	{
		m_flags &= ~EDN_WINDOW_RUNNING;
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_windowHandle);
		SDL_Quit();
	}

	bool Window::Initialize(WindowConfiguration & config)
	{
		setConfig(config);
		return Initialize();
	}

	bool Window::Initialize()
	{
		// Checking to see if we have ever passed a configuration to the window
		if (!configuration_passed)
			setConfig(default_configuration);

		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			Log() << "SDL failed to initialize";
		}

		m_windowHandle = SDL_CreateWindow(
			m_title.c_str(),
			m_position.x <= 0 ? SDL_WINDOWPOS_CENTERED : m_position.x,
			m_position.y <= 0 ? SDL_WINDOWPOS_CENTERED : m_position.y,
			m_size.width,
			m_size.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
		);

		if (!m_windowHandle)
		{
			Log() << "SDL failed to create window.";
			SDL_Quit();
			return false;
		}

		m_glContext = SDL_GL_CreateContext(m_windowHandle);
		
		if (!m_glContext)
		{
			Log() << "SDL failed to initialize OpenGL context";
			SDL_Quit();
		}

		// Initializeing glew and opengl
		glewExperimental = GL_TRUE;
		glewInit();

		m_flags |= EDN_WINDOW_RUNNING;
		return true;
	}

	void Window::SetClearColor(f32 r, f32 g, f32 b)
	{
		glClearColor(r, g, b, 1.0f);
	}

	void Window::SetClearColor(u32 hexcode)
	{
		f32 r = ((hexcode >> 16) & 0xFF) / 255.0f;
		f32 g = ((hexcode >>  8) & 0xFF) / 255.0f;
		f32 b = ((hexcode >>  0) & 0xFF) / 255.0f;
		SetClearColor(r, g, b);
	}

	void Window::SetTitle(String & title)
	{
		m_title = title;
		SDL_SetWindowTitle(m_windowHandle, m_title.c_str());
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Update()
	{
		Input & input = Input::Instance();
		if (input.KeySinglePress(KeyCode::KEY_ESC))
			m_flags &= ~EDN_WINDOW_RUNNING;
		if (input.KeySinglePress(KeyCode::KEY_RETURN))
			m_flags ^= EDN_WINDOW_FULLSCREEN;
		if (input.KeySinglePress(KeyCode::KEY_FORWARD_SLASH))
			m_flags ^= EDN_WINDOW_BOARDERLESS;

		// Update fullscreen
		if (IsFullscreen() != (SDL_GetWindowFlags(m_windowHandle) & SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP))
		{
			if (IsFullscreen())
				SDL_SetWindowFullscreen(m_windowHandle, SDL_WINDOW_FULLSCREEN_DESKTOP);
			else
				SDL_SetWindowFullscreen(m_windowHandle, 0);
		}

		// Updateing boarderless
		if (IsBoarderless() != (SDL_GetWindowFlags(m_windowHandle) & SDL_WINDOW_BORDERLESS))
		{
			if (IsBoarderless())
				SDL_SetWindowBordered(m_windowHandle, SDL_FALSE);
			else
				SDL_SetWindowBordered(m_windowHandle, SDL_TRUE);
		}

		// Update Vsync
		if (IsVsync() != (SDL_GL_GetSwapInterval()))
			SDL_GL_SetSwapInterval(IsVsync());

		// Update visable cursor
		if (IsHiddenCursor() != SDL_ShowCursor(SDL_QUERY) == 0)
		{
			if (IsHiddenCursor())
				SDL_ShowCursor(SDL_DISABLE);
			else
				SDL_ShowCursor(SDL_ENABLE);
		}

		// @Note: This should be in poll event under mouse movement. Store the delta of the mouse and
		// then set it back to the center of the screen.

		// Update cursor position if centering the cursor is enabled
		//if (IsCenterCursor())
		//{
		//	SDL_WarpMouseInWindow(m_windowHandle, m_center.x, m_center.y);
		//}
		input.Update();
	}

	void Window::PollEvents()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			{
				Cleanup();
			}
			break;

				//if (e.key.keysym.sym == SDLK_ESCAPE)
				//	m_flags &= ~EDN_WINDOW_RUNNING;
				//else if (e.key.keysym.sym == SDLK_RETURN)
				//	m_flags ^= EDN_WINDOW_FULLSCREEN;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
			case SDL_MOUSEMOTION:
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERAXISMOTION:
				Input::Instance().SDLEventHandle(e);
				break;
			case SDL_TEXTINPUT:
				break;
			
			case SDL_WINDOWEVENT:
			{
				switch (e.window.type)
				{
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_EXPOSED:
				case SDL_WINDOWEVENT_MOVED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
				case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
				case SDL_WINDOWEVENT_CLOSE:
				case SDL_WINDOWEVENT_RESIZED:
					break;
				default:
					break;
				}
			}break;
			
			}
		}
	}

	void Window::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_windowHandle);
	}

	void Window::setConfig(WindowConfiguration & config)
	{
		m_title = config.title;
		m_size = { config.width, config.height };
		m_position = { config.x, config.y };
		m_center = { config.width / 2, config.height / 2 };
		m_flags = config.flags;
		configuration_passed = true;
	}
}