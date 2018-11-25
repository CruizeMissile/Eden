#pragma once

#include "surface.hpp"
#include "window_flags.hpp"
#include <memory>

namespace eden::input
{
enum class key_t;
}

namespace eden::render
{
class window_t : public surface_t
{
public:
    static std::unique_ptr<window_t> create(const window_descriptor_t& desc);

    virtual offset2_t position() const = 0;
    virtual window_t& position(const offset2_t& position) = 0;

    virtual extent2_t size(bool use_client_are = true) const = 0;
    virtual window_t& size(const extent2_t& size, bool use_client_area) = 0;

    virtual std::string title() const = 0;
    virtual window_t& title(const std::string& title) = 0;

    virtual window_descriptor_t descriptor() const = 0;
    virtual window_t& descriptor(const window_descriptor_t& desc) = 0;

    const window_behavior_t& behavior() const;
    window_t& behavior(const window_behavior_t& behav);

    virtual void show(bool should_show = true) = 0;
    virtual bool is_shown() const = 0;
    virtual bool has_focus() const;

    bool adapt_for_video_mode(video_mode_descriptor_t& desc) override;
    bool process_events();

    // Post events
    void post_key_down(input::key_t key);
    void post_key_up(input::key_t key);
    void post_double_click(input::key_t key);
    void post_char(char chr);
    void post_wheel_motion(int motion);
    void post_local_motion(const offset2_t& position);
    void post_global_motion(const offset2_t& motion);
    void post_resize(const extent2_t& client_area);
    void post_get_focus();
    void post_lose_forcus();
    void post_quit();

protected:
    virtual void on_process_events() = 0;

private:
    window_behavior_t behavior_;
    bool quit_ = false;
    bool has_focus_ = false;
};
} // namespace eden::render
