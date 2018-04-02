
#include "window.hpp"

#include <GLFW/glfw3.h>
#include <pride/assert.hpp>
#include <iostream>
#include <string>

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

void error_callback(int error, const char* description)
{
    std::cout << "Error(" << error << "): " << description << '\n';
}

namespace eden
{
    const window_t::info_t window_t::info_t::default =
    {
        "Eden Engine", 1280, 720, false, true, true
    };

    window_t::~window_t()
    {
        glfwTerminate();
    }

    void window_t::create_window(const window_t::info_t& info)
    {
        glfwSetErrorCallback(error_callback);
        if (!glfwInit())
            std::cout << "glfw init failed\n";

        title = info.title;
        width = info.width;
        height = info.height;

        setup_glfw_window_hints();

        window_ptr = glfwCreateWindow(width, height, title.c_str(), 0, 0);
        if (!window_ptr)
            std::cout << "glfw create window failed\n";

        // Before opengl context have to make the gl context current
        glfwMakeContextCurrent(window_ptr);

        // Setting input events and callbacks
        //glfwSetKeyCallback(window_ptr, key_callback);
        //glfwSetMouseButtonCallback(window_ptr, mouse_callback);
        //glfwSetScrollCallback(window_ptr, scroll_callback);
        //glfwSetCursorPosCallback(window_ptr, cursor_position_callback);
        //glfwSetCursorEnterCallback(window_ptr, cursor_enter_callback);
        //glfwSetDropCallback(window_ptr, drop_callback);
        //glfwSetJoystickCallback(joystick_callback);
        //glfwSetCharCallback(window_ptr, character_callback); // text input
        //glfwSetCharModsCallback(window_ptr, charmods_callback);
    }

    bool window_t::check_running_status()
    {
        return glfwGetKey(window_ptr, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window_ptr) == 0;
    }

    void window_t::process_os_events()
    {
        glfwSwapBuffers(window_ptr);
        glfwPollEvents();
    }

    u32 window_t::get_width() const noexcept
    {
        return width;
    }

    u32 window_t::get_height() const noexcept
    {
        return height;
    }

    bool window_t::is_fullscreen() const noexcept
    {
        return fullscreen;
    }

    bool window_t::is_bordered() const noexcept
    {
        return bordered;
    }

    bool window_t::is_resizeable() const noexcept
    {
        return resizeable;
    }

    void window_t::set_fullscreen(const bool fullscreen) noexcept
    {
        if (this->fullscreen == fullscreen)
            return;

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
        {
            glfwSetWindowMonitor(window_ptr, 0, xpos, ypos, width, height, 0);
        }

        this->fullscreen = fullscreen;
    }

    void window_t::set_bordered(const bool bordered) noexcept
    {
        this->bordered = bordered;
    }

    void window_t::set_resizable(const bool resizable) noexcept
    {
        this->resizeable = resizable;
    }

    void window_t::set_cursor_position(u32 x, u32 y)
    {
        glfwSetCursorPos(window_ptr, static_cast<f64>(x), static_cast<f64>(y));
    }

    void window_t::get_cursor_position()
    {

    }

}
