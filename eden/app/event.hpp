
#pragma once

#include <pride/config/detection.hpp>
#include <pride/utility/singleton.hpp>

#include <functional>
#include <memory>
#include <queue>
#include <vector>

namespace eden
{
    template <typename EventType>
    class listener_t;
    template <typename derived>
    class event_t;

    // --------------------------------------------------------------------------------------------

    class event_base_t
    {
    public:
        virtual ~event_base_t() = default;
        virtual bool has_listeners() const = 0;
        virtual void raise() const = 0;
    };

    // --------------------------------------------------------------------------------------------

    template <typename EventType>
    class listener_t
    {
        static_assert(std::is_base_of<event_base_t, EventType>::value, "Template argument must inherit from Event.");
    public:
        using EventFunc = void(const EventType&);
        listener_t();
        listener_t(const std::function<EventFunc>& callback_func);
        listener_t(std::function<EventFunc>&& callback_func);
        ~listener_t();

        std::function<void(const EventType&)> callback;
    };

    // --------------------------------------------------------------------------------------------

    template <typename Derived>
    class event_t : public event_base_t
    {
    public:
        virtual ~event_t() = default;

        virtual bool has_listeners() const final override;
        virtual void raise() const final override;

        static void subscribe(listener_t<Derived>& listener);
        static void unsubscribe(listener_t<Derived>& listener);
        static bool has_listeners_static();

    private:
        static std::vector<listener_t<Derived>*> _listeners;
    };

    // --------------------------------------------------------------------------------------------

    class event_queue_t : public pride::singleton_t<event_queue_t>
    {
    public:
        void push(std::unique_ptr<event_base_t> e);
        void dispatch(const event_base_t& e) const;
        void dispatch();

    private:
        std::queue<std::unique_ptr<event_base_t>> _queue;
    };
}

#include "event.inl"
