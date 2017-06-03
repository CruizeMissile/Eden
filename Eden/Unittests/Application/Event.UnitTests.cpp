#include "UnitTest.h"
#include "Application/Event.h"

struct KeyPressed : public edn::Event<KeyPressed>
{
	KeyPressed(const u32 key) : key(key) {}
	const u32 key;
};

TEST_CASE("Events")
{
	using namespace edn;
	SECTION("key pressed")
	{
		std::vector<u32> list;

		auto compare = [](auto& one, auto& two)
		{
			return std::equal(one.begin(), one.end(), two.begin());
		};
		
		// Create the listener
		Listener<KeyPressed> listener;
		listener.callback = [&](auto& e) 
		{
			list.push_back(e.key);
		};

		// Push an event in the queue
		EventQueue.Push(std::make_unique<KeyPressed>(static_cast<u32>(1u)));
		EventQueue.Push(std::make_unique<KeyPressed>(static_cast<u32>(2u)));
		EventQueue.Push(std::make_unique<KeyPressed>(static_cast<u32>(3u)));
		EventQueue.Push(std::make_unique<KeyPressed>(static_cast<u32>(4u)));
		EventQueue.Push(std::make_unique<KeyPressed>(static_cast<u32>(5u)));

		EventQueue.Dispatch(KeyPressed(6u));

		// The event should have fired and is even should be true
		std::vector<u32> result1 = { 6 };
		CHECK(compare(list, result1));

		EventQueue.Dispatch();

		// Event queue is processed and is_even should be false
		std::vector<u32> result2 = { 6, 1, 2, 3, 4, 5 };
		CHECK(compare(list, result2));
	}
}