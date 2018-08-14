
#include "window.hpp"
#include "input.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <pride/assert.hpp>
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

void key_callback(GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mods)
{
    if (action == GLFW_REPEAT) return;
    eden::input_t::instance().set_key_state(static_cast<eden::key_t>(key), action == GLFW_PRESS);
    if (action == GLFW_PRESS)
        eden::event_queue_t::instance().push(std::make_unique<eden::events::key_down_t>(static_cast<eden::key_t>(key)));
    else
        eden::event_queue_t::instance().push(std::make_unique<eden::events::key_up_t>(static_cast<eden::key_t>(key)));
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_REPEAT) return;
    eden::input_t::instance().set_mouse_btn_state(static_cast<eden::mouse_button_t>(button), action == GLFW_PRESS || action == GLFW_REPEAT);
    if (action == GLFW_PRESS)
        eden::event_queue_t::instance().push(std::make_unique<eden::events::mouse_button_down_t>(static_cast<eden::mouse_button_t>(button)));
    else
        eden::event_queue_t::instance().push(std::make_unique<eden::events::mouse_button_up_t>(static_cast<eden::mouse_button_t>(button)));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << xoffset << " " << yoffset << '\n';
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    eden::input_t::instance().update_cursor_position(static_cast<s32>(xpos), static_cast<s32>(ypos));
    eden::event_queue_t::instance().push(std::make_unique<eden::events::mouse_movement_t>(static_cast<u32>(xpos), static_cast<u32>(ypos)));
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (entered)
        eden::event_queue_t::instance().push(std::make_unique<eden::events::window_entered_t>());
    else
        eden::event_queue_t::instance().push(std::make_unique<eden::events::window_exited_t>());
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0; i < count; i++)
        eden::event_queue_t::instance().push(std::make_unique<eden::events::drag_and_drop_t>(paths[i]));
}

void joystick_callback(s32 joy_idx, s32 event)
{
    //if (event == GLFW_CONNECTED)
    //    // joystick connected
    //else if (event == GLFW_DISCONNECTED)
    //    // joystick disconnected
}

namespace eden
{
const window_t::info_t window_t::info_t::default_config = {
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
    glfwSetKeyCallback(window_ptr, key_callback);
    glfwSetMouseButtonCallback(window_ptr, mouse_callback);
    glfwSetScrollCallback(window_ptr, scroll_callback);
    glfwSetCursorPosCallback(window_ptr, cursor_position_callback);
    glfwSetCursorEnterCallback(window_ptr, cursor_enter_callback);
    glfwSetDropCallback(window_ptr, drop_callback);
    glfwSetJoystickCallback(joystick_callback);
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

} // namespace eden
