#include "Precompiled.h"
#include "Window.h"

namespace edn
{
	Window::Window()
		: m_windowFlags(0)
	{
		m_title = "Eden Engine";
		m_resolution={ 1270, 720 };
		m_position={ 0, 0 };
		m_center={ m_resolution.width / 2, m_resolution.height / 2 };
		m_windowFlags |= EDN_WINDOW_VSYNC;
	}

	Window::Window(String title, IRect resultion, IPoint position, u32 flags)
		: m_windowFlags(flags)
		, m_title(title)
		, m_resolution(m_resolution)
		, m_position(position)
	{
		m_center={ m_resolution.width / 2, m_resolution.height / 2 };
	}

	Window::~Window()
	{
		Cleanup();
	}

	void Window::Cleanup()
	{
		m_windowFlags &= ~EDN_WINDOW_RUNNING;
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_windowHandle);
		SDL_Quit();
	}

	bool Window::Initialize()
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			Log() << "SDL failed to initialize";
		}

		m_windowHandle = SDL_CreateWindow(
			m_title.c_str(),
			m_position.x <= 0 ? SDL_WINDOWPOS_CENTERED : m_position.x,
			m_position.y <= 0 ? SDL_WINDOWPOS_CENTERED : m_position.y,
			m_resolution.width,
			m_resolution.height,
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

		m_windowFlags |= EDN_WINDOW_RUNNING;
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

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Update()
	{
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

			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					m_windowFlags &= ~EDN_WINDOW_RUNNING;
				else if (e.key.keysym.sym == SDLK_RETURN)
					m_windowFlags ^= EDN_WINDOW_FULLSCREEN;
				break;

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
}