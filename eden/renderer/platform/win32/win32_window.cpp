#include "win32_window.hpp"
#include "win32_callback.hpp"

namespace eden::render
{
// ────────────────────────────────────────────────────────────────────────────────
// Internal sturctures and functions for coping with the horror that is win32 api

struct window_appearance_t
{
    DWORD style = 0;
    offset2_t position;
    extent2_t size;
};

static void set_user_data(HWND wnd, void* userData)
{
    SetWindowLongPtr(wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));
}

static RECT get_client_area(LONG width, LONG height, DWORD style)
{
    RECT rc;
    {
        rc.left = 0;
        rc.top = 0;
        rc.right = width;
        rc.bottom = height;
    }
    AdjustWindowRect(&rc, style, FALSE);
    return rc;
}

static DWORD get_window_style(const window_descriptor_t& desc)
{
    DWORD style = (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

    if (desc.context != nullptr && reinterpret_cast<const native_content_handle_t*>(desc.context)->parent != 0)
        style |= WS_CHILD;
    else if (desc.borderless)
        style |= WS_POPUP;
    else
    {
        style |= (WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION);
        if (desc.resizable)
            style |= (WS_SIZEBOX | WS_MAXIMIZEBOX);
    }

    if (desc.visible)
        style |= WS_VISIBLE;

    return style;
}

static offset2_t get_screen_center_position(const extent2_t& size)
{
    return {
        GetSystemMetrics(SM_CXSCREEN) / 2 - (static_cast<int>(size.width) / 2),
        GetSystemMetrics(SM_CYSCREEN) / 2 - (static_cast<int>(size.height) / 2)
    };
}

static window_appearance_t get_window_appearance(const window_descriptor_t& desc)
{
    window_appearance_t appearance;

    /* Get window style and client area */
    appearance.style = get_window_style(desc);

    auto rc = get_client_area(
        static_cast<LONG>(desc.size.width),
        static_cast<LONG>(desc.size.height),
        appearance.style);

    /* Setup window size */
    appearance.size.width = static_cast<std::uint32_t>(rc.right - rc.left);
    appearance.size.height = static_cast<std::uint32_t>(rc.bottom - rc.top);

    /* Setup window position */
    appearance.position = (desc.centered ? get_screen_center_position(desc.size) : desc.position);

    if (desc.centered)
    {
        appearance.position.x += rc.left;
        appearance.position.y += rc.top;
    }

    return appearance;
}

// ────────────────────────────────────────────────────────────────────────────────

std::unique_ptr<window_t> window_t::create(const window_descriptor_t& desc)
{
    return std::make_unique<win32_window_t>(desc);
}

win32_window_t::win32_window_t(const window_descriptor_t& desc)
    : context_handle_{ 0 }
    , wnd_(create_window_handle(desc))
{
}

win32_window_t::~win32_window_t()
{
    if (wnd_)
        DestroyWindow(wnd_);
}

void win32_window_t::get_native_handle(void* handle) const
{
    auto h = reinterpret_cast<native_handle_t*>(handle);
    h->window = wnd_;
}

void win32_window_t::reset_pixel_format()
{
    auto desc = descriptor();
    DestroyWindow(wnd_);
    wnd_ = create_window_handle(desc);
}

extent2_t win32_window_t::get_content_size() const
{
    return size(true);
}

offset2_t win32_window_t::position() const
{
    RECT r;
    GetWindowRect(wnd_, &r);
    MapWindowPoints(HWND_DESKTOP, GetParent(wnd_), reinterpret_cast<LPPOINT>(&r), 2);
    return { r.left, r.top };
}

window_t& win32_window_t::position(const offset2_t& position)
{
    SetWindowPos(wnd_, HWND_TOP, position.x, position.y, 0, 0, (SWP_NOSIZE | SWP_NOZORDER));
    return *this;
}

extent2_t win32_window_t::size(bool use_client_area) const
{
    RECT r;
    if (use_client_area)
    {
        GetClientRect(wnd_, &r);
        return {
            static_cast<uint32_t>(r.right - r.left),
            static_cast<uint32_t>(r.bottom - r.top)
        };
    }
    else
    {
        GetWindowRect(wnd_, &r);
        return {
            static_cast<uint32_t>(r.right - r.left),
            static_cast<uint32_t>(r.bottom - r.top)
        };
    }
}

window_t& win32_window_t::size(const extent2_t& size, bool use_client_area)
{
    int cx, cy = 0;
    if (use_client_area)
    {
        auto r = get_client_area(
            static_cast<LONG>(size.width),
            static_cast<LONG>(size.height),
            GetWindowLong(wnd_, GWL_STYLE));
        cx = r.right - r.left;
        cy = r.bottom - r.top;
    }
    else
    {
        cx = static_cast<int>(size.width);
        cx = static_cast<int>(size.height);
    }

    SetWindowPos(wnd_, HWND_TOP, 0, 0, cx, cy, (SWP_NOMOVE | SWP_NOZORDER));
    return *this;
}

std::string win32_window_t::title() const
{
    return "TODO";
}

window_t& win32_window_t::title(const std::string& title)
{
    return *this;
}

window_descriptor_t win32_window_t::descriptor() const
{
    auto window_flags = GetWindowLong(wnd_, GWL_STYLE);
    auto window_size = size();
    auto center_point = get_screen_center_position(window_size);

    window_descriptor_t desc;
    desc.position = position();
    desc.size = window_size;
    desc.visible = ((window_flags & WS_VISIBLE) != 0);
    desc.borderless = ((window_flags & WS_CAPTION) == 0);
    desc.resizable = ((window_flags & WS_SIZEBOX) != 0);
    desc.centered = (center_point.x == desc.position.x && center_point.y == desc.position.y);
    desc.context = (context_handle_.parent != 0 ? (&context_handle_) : nullptr);

    return desc;
}

window_t& win32_window_t::descriptor(const window_descriptor_t& desc)
{
    auto window_flags = GetWindowLong(wnd_, GWL_STYLE);
    auto borderless = ((window_flags & WS_CAPTION) == 0);
    auto resizable = ((window_flags & WS_SIZEBOX) != 0);

    auto new_flags = get_window_style(desc);

    if ((window_flags & WS_MAXIMIZE) != 0)
        new_flags |= WS_MAXIMIZE;
    if ((window_flags & WS_MINIMIZE) != 0)
        new_flags |= WS_MINIMIZE;

    auto flags_changed = (window_flags != new_flags);

    auto window_position = position();
    auto window_size = size();

    bool position_changed = (desc.position.x != window_position.x || desc.position.y != window_position.y);
    bool size_changed = (desc.size.width != window_size.width || desc.size.height != window_size.height);

    if (flags_changed || position_changed || size_changed)
    {
        // reset user data to avoid recursive resize
        set_user_data(wnd_, nullptr);

        UINT flags = SWP_NOZORDER;
        if (flags_changed)
        {
            ShowWindow(wnd_, SW_HIDE);
            SetWindowLongPtr(wnd_, GWL_STYLE, new_flags);
            flags |= SWP_FRAMECHANGED;
        }

        auto appearance = get_window_appearance(desc);
        if (desc.visible)
            flags |= SWP_FRAMECHANGED;
        if ((new_flags & WS_MAXIMIZE) != 0)
            flags |= (SWP_NOSIZE | SWP_NOMOVE);

        if (borderless == desc.borderless && resizable == desc.resizable)
        {
            if (!position_changed)
                flags |= SWP_NOMOVE;
            if (!size_changed)
                flags |= SWP_NOSIZE;
        }

        SetWindowPos(
            wnd_,
            0,
            appearance.position.x,
            appearance.position.y,
            static_cast<int>(appearance.size.width),
            static_cast<int>(appearance.size.height),
            flags);

        set_user_data(wnd_, this);
    }
    return *this;
}

void win32_window_t::show(bool should_show)
{
    ShowWindow(wnd_, (should_show ? SW_NORMAL : SW_HIDE));
}

bool win32_window_t::is_shown() const
{
    return (IsWindowVisible(wnd_) ? true : false);
}

HWND win32_window_t::create_window_handle(const window_descriptor_t& desc)
{
    WNDCLASS wc = { 0 };
    wc.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS);
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpfnWndProc = reinterpret_cast<WNDPROC>(internal::win32_window_callback);
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(DKGRAY_BRUSH));
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = "__EDEN_WIN32_WINDOW_CLASS__";

    RegisterClass(&wc);

    auto appearance = get_window_appearance(desc);
    HWND parent_wnd = HWND_DESKTOP;
    if (auto context = reinterpret_cast<const native_content_handle_t*>(desc.context))
    {
        if (context->parent)
        {
            parent_wnd = context->parent;
            context_handle_ = *context;
        }
    }

    HWND wnd = CreateWindow(
        "__EDEN_WIN32_WINDOW_CLASS__",
        "win32 eden engine",
        appearance.style,
        appearance.position.x,
        appearance.position.y,
        static_cast<int>(appearance.size.width),
        static_cast<int>(appearance.size.height),
        parent_wnd,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr);

    if (!wnd)
        throw std::runtime_error("failed to create window");

    set_user_data(wnd, this);
    return wnd;
}

void win32_window_t::on_process_events()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
} // namespace eden::render
