#pragma once
#include "Application/WindowInfo.h"
#include "Application/Event.h"

namespace edn
{
    class GLFWwindow;

    class Window
    {
        friend class Application;
    public:
        Window();
        ~Window();

        void createWindow(const WindowInfo& create_info = WindowInfo::Default);

        bool checkRunningStatus();

        u32 getWidth() { return width; }
        u32 getHeight() { return height; }

        bool isFullscreen() { return is_fullscreen; }
        bool isBordered() { return is_bordered; }
        bool isResizable() { return is_resizeable; }

        bool setFullscreen(bool fullscreen);
        bool setBordered(bool bordered);
        bool setResizable(bool bordered);

        void processOsEvents();

    protected:
        void setCursorPosition(s32 x, s32 y);
        void getCursorPosition();

    private:
        String title;
        u32 width;
        u32 height;
        s32 xpos;
        s32 ypos;

        bool is_fullscreen = false;
        bool is_bordered = true;
        bool is_resizeable = true;
    };

    namespace evn
    {
        struct WindowEntered : public Event<WindowEntered> {};
        struct WindowExit: public Event<WindowExit> {};
    }
}
