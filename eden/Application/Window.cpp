#include "Precompiled.h"
#include "Application/Application.h"
#include "Application/Window.h"
#include "Application/Input.h"
#include "GLFW/glfw3.h"

using namespace std;

GLFWwindow* window_ptr;

void setup_glfw_window_hints()
{
    // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void key_callback(GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mods)
{
    if (action == GLFW_REPEAT) return;
    edn::Input.setKeyState(static_cast<edn::Key>(key), action == GLFW_PRESS);
    if (action == GLFW_PRESS)
        edn::EventQueue.push(std::make_unique<edn::evn::KeyDown>(static_cast<edn::Key>(key)));
    else
        edn::EventQueue.push(std::make_unique<edn::evn::KeyUp>(static_cast<edn::Key>(key)));
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_REPEAT) return;
    edn::Input.setMouseBtnState(static_cast<edn::MouseButton>(button), action == GLFW_PRESS || action == GLFW_REPEAT);
    if (action == GLFW_PRESS)
        edn::EventQueue.push(std::make_unique<edn::evn::MouseButtonDown>(static_cast<edn::Key>(button)));
    else
        edn::EventQueue.push(std::make_unique<edn::evn::MouseButtonUp>(static_cast<edn::Key>(button)));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cout << xoffset << " " << yoffset << endl;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    edn::Input.updateCursorPosition(static_cast<s32>(xpos), static_cast<s32>(ypos));
    edn::EventQueue.push(std::make_unique<edn::evn::MouseMovement>(static_cast<u32>(xpos), static_cast<u32>(ypos)));
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (entered)
        edn::EventQueue.push(std::make_unique<edn::evn::WindowEntered>());
    else
        edn::EventQueue.push(std::make_unique<edn::evn::WindowExit>());
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0; i < count; i++)
        edn::EventQueue.push(std::make_unique<edn::evn::DragAndDrop>(paths[i]));
}

void joystick_callback(s32 joy_idx, s32 event)
{
    //if (event == GLFW_CONNECTED)
    //    // joystick connected
    //else if (event == GLFW_DISCONNECTED)
    //    // joystick disconnected
}


namespace edn
{
    Window::Window()
    {
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::createWindow(const WindowInfo& info)
    {
        if (!glfwInit())
            cout << "glfw init failed" << endl;

        title = info.title;
        width = info.width;
        height = info.height;

        setup_glfw_window_hints();

        window_ptr = glfwCreateWindow(width, height, title.c_str(), 0, 0);

        if (!window_ptr)
            cout << "glfw create window failed" << endl;

        // Before opengl context have to make the gl context current
        glfwMakeContextCurrent(window_ptr);

        // Setting input events and callbacks
        glfwSetKeyCallback(window_ptr, key_callback);
        glfwSetMouseButtonCallback(window_ptr, mouse_callback);
        glfwSetScrollCallback(window_ptr, scroll_callback);
        glfwSetCursorPosCallback(window_ptr, cursor_position_callback);
        glfwSetCursorEnterCallback(window_ptr, cursor_enter_callback);
        glfwSetDropCallback(window_ptr, drop_callback);
        glfwSetJoystickCallback(joystick_callback);
        //glfwSetCharCallback(window_ptr, character_callback); // text input
        //glfwSetCharModsCallback(window_ptr, charmods_callback);

        setFullscreen(info.fullscreen);
    }

    bool Window::checkRunningStatus()
    {
        return glfwGetKey(window_ptr, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window_ptr) == 0;
    }

    void Window::processOsEvents()
    {
        glfwSwapBuffers(window_ptr);
        glfwPollEvents();
    }

    bool Window::setFullscreen(bool fullscreen)
    {
        if (is_fullscreen == fullscreen)
            return true;

        if (fullscreen)
        {
            auto monitor = glfwGetPrimaryMonitor();
            if (monitor)
            {
                const auto mode = glfwGetVideoMode(monitor);
                glfwGetWindowPos(window_ptr, &xpos, &ypos);
                glfwSetWindowMonitor(window_ptr, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
        }
        else
            glfwSetWindowMonitor(window_ptr, 0, xpos, ypos, width, height, 0);

        is_fullscreen = fullscreen;
        return true;
    }

    bool Window::setBordered(bool bordered)
    {
        return true;
    }

    bool Window::setResizable(bool bordered)
    {
        return true;
    }
    void Window::setCursorPosition(s32 x, s32 y)
    {
        glfwSetCursorPos(window_ptr, static_cast<f64>(x), static_cast<f64>(y));
    }
}
