#pragma once
#include "Application/Window.h"
#include "Core/Platform.h"
#include "Core/Singleton.h"
#include "Core/Types.h"


namespace edn
{
    static class Application : public Singleton<class Application>
    {
        friend class Input;
    public:
        Application() {}
        ~Application() {}

        void createWindow(const WindowInfo& info = WindowInfo::Default);
        void update();
        void shutdown() { running = false; }

        bool running;
        Window window;
    private:
        void getCursorPosition();
        void setCursorPosition(s32 x, s32 y);
    } &App = Singleton<class Application>::instanceRef;
}
