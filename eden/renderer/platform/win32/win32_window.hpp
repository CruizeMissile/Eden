#pragma once

#include "../../window.hpp"
#include "../native_handle.hpp"

namespace eden::render
{
class win32_window_t : public window_t
{
public:
    win32_window_t(const window_descriptor_t& desc);
    ~win32_window_t();

    void get_native_handle(void* handle) const override;
    void reset_pixel_format() override;

    extent2_t get_content_size() const override;

    offset2_t position() const override;
    window_t& position(const offset2_t& position) override;

    extent2_t size(bool use_client_area = true) const override;
    window_t& size(const extent2_t& size, bool use_client_area) override;

    std::string title() const override;
    window_t& title(const std::string& title) override;

    window_descriptor_t descriptor() const override;
    window_t& descriptor(const window_descriptor_t& desc) override;

    void show(bool should_show = true) override;
    bool is_shown() const override;

protected:
    void on_process_events() override;

private:
    HWND create_window_handle(const window_descriptor_t& desc);

    window_descriptor_t desc_;
    native_content_handle_t context_handle_;
    HWND wnd_ = nullptr;
};
} // namespace eden::render
