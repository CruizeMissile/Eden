
#include "window.hpp"

namespace eden::render
{
const window_behavior_t& window_t::behavior() const
{
    return behavior_;
}

window_t& window_t::behavior(const window_behavior_t& behav)
{
    behavior_ = behav;
    return *this;
}

bool window_t::has_focus() const
{
    return has_focus_;
}

bool window_t::adapt_for_video_mode(video_mode_descriptor_t& video_mode_desc)
{
    auto desc = descriptor();

    desc.size = video_mode_desc.resolution;

    if (video_mode_desc.fullscreen)
    {
        desc.borderless = true;
        desc.position = { 0, 0 };
    }
    else
    {
        desc.borderless = false;
        desc.centered = true;
    }

    descriptor(desc);
    return true;
}

bool window_t::process_events()
{
    on_process_events();
    return !quit_;
}

void window_t::post_key_down(input::key_t key)
{
}

void window_t::post_key_up(input::key_t key)
{
}

void window_t::post_double_click(input::key_t key)
{
}

void window_t::post_char(char chr)
{
}

void window_t::post_wheel_motion(int motion)
{
}

void window_t::post_local_motion(const offset2_t& position)
{
}

void window_t::post_global_motion(const offset2_t& motion)
{
}

void window_t::post_resize(const extent2_t& client_area)
{
}

void window_t::post_get_focus()
{
    has_focus_ = true;
}

void window_t::post_lose_forcus()
{
    has_focus_ = false;
}

void window_t::post_quit()
{
    quit_ = true;
}

} // namespace eden::render
