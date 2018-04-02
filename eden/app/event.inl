
#include <algorithm>

namespace eden
{
    template<typename Derived>
    std::vector<listener_t<Derived>*> event_t<Derived>::_listeners;

    // ---------------------------------------------------------------------------------------------
    // listener_t

    template<typename EventType>
    listener_t<EventType>::listener_t()
    {
        EventType::subscribe(*this);
    }

    template<typename EventType>
    listener_t<EventType>::listener_t(const std::function<EventFunc>& callback_func)
    : callback(callback_func)
    {
        EventType::subscribe(*this);
    }

    template<typename EventType>
    listener_t<EventType>::listener_t(std::function<EventFunc>&& callback_func)
    : callback(std::move(callback_func))
    {
        EventType::subscribe(*this);
    }

    template<typename EventType>
    listener_t<EventType>::~listener_t()
    {
        EventType::unsubscribe(*this);
    }

    // ---------------------------------------------------------------------------------------------
    // event_t

    template <typename Derived>
    bool event_t<Derived>::has_listeners() const
    {
        return has_listeners_static();
    }

    template <typename Derived>
    void event_t<Derived>::raise() const
    {
        for(auto listener : _listeners)
        {
            if (listener->callback)
                listener->callback(*static_cast<const Derived*>(this));
        }
    }

    template <typename Derived>
    void event_t<Derived>::subscribe(listener_t<Derived>& listener)
    {
        _listeners.push_back(&listener);
    }

    template <typename Derived>
    void event_t<Derived>::unsubscribe(listener_t<Derived>& listener)
    {
        _listeners.erase(std::find(_listeners.begin(), _listeners.end(), &listener));
    }

    template <typename Derived>
    bool event_t<Derived>::has_listeners_static()
    {
        return !_listeners.empty();
    }

    // ---------------------------------------------------------------------------------------------
    // event_queue_t

    inline void event_queue_t::push(std::unique_ptr<event_base_t> e)
    {
        if (e->has_listeners())
            _queue.push(std::move(e));
    }

    inline void event_queue_t::dispatch(const event_base_t& e) const
    {
        e.raise();
    }

    inline void event_queue_t::dispatch()
    {
        while (!_queue.empty())
        {
            _queue.front()->raise();
            _queue.pop();
        }
    }
}
