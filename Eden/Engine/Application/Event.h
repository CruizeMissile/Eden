#pragma once
#include "Core/Singleton.h"
#include "Core/Platform.h"
#include <functional>
#include <memory>
#include <queue>
#include <vector>

#if defined(EDN_DEBUG)
	#include "Core/Debug.h"
#endif

namespace edn
{
	class EventBase 
	{
	public:
		virtual ~EventBase() = default;
		virtual void raise()const = 0;
		virtual bool has_listeners()const = 0;
	};


	template<class EventType>
	class Listener
	{
		//friend EventType;
		static_assert(std::is_base_of<EventBase, EventType>::value, "Template does not inherit from Event.");
	public:
		Listener()
		{
			EventType::subscribe(*this);
		}

		Listener(std::function<void(const EventType&)> callback)
			: callback(callback)
		{
			EventType::subscribe(*this);
		}

		~Listener()
		{
			EventType::unsubscribe(*this);
		}
		std::function<void(const EventType&)> callback = nullptr;
	};


	template<class Derived>
	class Event : public EventBase
	{
		friend Listener<Derived>;
	public:
		virtual ~Event() = default;

		virtual void raise() const
		{
			for (auto i = 0u ; i < _listeners.size() ; ++i)
			{
				if (_listeners[i]->callback)
					_listeners[i]->callback(*static_cast<const Derived*>(this));
			}
		}
		virtual bool has_listeners() const final override { return has_listeners_static(); }
		static bool has_listeners_static() { return !_listeners.empty(); }
		
		static const auto& get_listeners() { return _listeners; }
	
	private:
		static void subscribe(Listener<Derived>& listener) { _listeners.push_back(&listener); }
		static void unsubscribe(Listener<Derived>& listener) { _listeners.erase(std::find(_listeners.begin(), _listeners.end(), &listener)); }

		static std::vector<Listener<Derived>*> _listeners;
	};
	template<class Derived> std::vector<Listener<Derived>*> Event<Derived>::_listeners;


	static class EventQueue : public Singleton<class EventQueue>
	{
	public:
		void push(std::unique_ptr<EventBase> e)
		{
			#if defined(EDN_DEBUG)
				ASSERT(!is_dispatching, "Cannot push an event while event queue is being processed. Try calling Dispatch(const EventBase&) to bypass the event queue.");
			#endif
			if (e->has_listeners())
				_queue.push(std::move(e));
		}

		void dispatch(const EventBase& e)
		{
			e.raise();
		}

		void dispatch()
		{
			#if defined (EDN_DEBUG)
				is_dispatching = true;
			#endif

			// Note: This can be changed for a cuncurrent queue to handle multi-threading. Just an thought.
			while (!_queue.empty())
			{
				_queue.front()->raise();
				_queue.pop();
			}

			#if defined (EDN_DEBUG)
				is_dispatching = false;
			#endif
		}

	private:
		#if defined (EDN_DEBUG)
			bool is_dispatching = false;
		#endif
		
		std::queue<std::unique_ptr<class EventBase>> _queue;

	} &EventQueue = Singleton<class EventQueue>::instanceRef;
}