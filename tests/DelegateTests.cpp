#include <optional>
#include <vector>

#include <catch2/catch_all.hpp>

#include <GCore/Delegate.hpp>

using namespace Gadget;

TEST_CASE("Delegate::Broadcast", "[delegate_broadcast]")
{
	SECTION("Empty broadcast is a safe no-op")
	{
		Delegate<void()> delegate;
		delegate.Broadcast();
	}

	SECTION("Invokes active listeners and skips expired handles")
	{
		Delegate<void()> delegate;
		int firstListenerCalls = 0;
		int expiredListenerCalls = 0;
		int lastListenerCalls = 0;

		const auto firstHandle = delegate.Add([&](){ ++firstListenerCalls; });
		auto expiringHandle = std::make_optional(delegate.Add([&](){ ++expiredListenerCalls; }));
		const auto lastHandle = delegate.Add([&](){ ++lastListenerCalls; });

		delegate.Broadcast();
		REQUIRE(firstListenerCalls == 1);
		REQUIRE(expiredListenerCalls == 1);
		REQUIRE(lastListenerCalls == 1);

		// Dropping a DelegateHandle automatically unsubscribes its callback
		expiringHandle.reset();

		delegate.Broadcast();
		REQUIRE(firstListenerCalls == 2);
		REQUIRE(expiredListenerCalls == 1);
		REQUIRE(lastListenerCalls == 2);
	}

	SECTION("Forwards arguments to bound listeners")
	{
		Delegate<void(int, double)> delegate;
		int receivedInt = 0;
		double receivedDouble = 0.0;

		const auto handle = delegate.Add([&](int a, double b)
		{
			receivedInt = a;
			receivedDouble = b;
		});

		delegate.Broadcast(42, 3.5);
		REQUIRE(receivedInt == 42);
		REQUIRE(receivedDouble == 3.5);
	}

	SECTION("Adding listeners inside Broadcast survives vector reallocation and defers new listeners")
	{
		Delegate<void()> delegate;
		std::vector<DelegateHandle<void()>> addedHandles;
		addedHandles.shrink_to_fit();

		int initialListenerCalls = 0;
		int trailingListenerCalls = 0;
		int addedListenerCalls = 0;

		const auto initialHandle = delegate.Add([&]()
		{
			++initialListenerCalls;
			if (addedHandles.empty())
			{
				// Push enough listeners to force callbacks vector reallocation mid-Broadcast
				for (int i = 0; i < 32; ++i)
				{
					addedHandles.push_back(delegate.Add([&](){ ++addedListenerCalls; }));
				}
			}
		});

		const auto trailingHandle = delegate.Add([&](){ ++trailingListenerCalls; });

		delegate.Broadcast();
		REQUIRE(initialListenerCalls == 1);
		REQUIRE(trailingListenerCalls == 1);
		// Newly registered listeners should not fire on the event that added them
		REQUIRE(addedListenerCalls == 0);

		delegate.Broadcast();
		REQUIRE(initialListenerCalls == 2);
		REQUIRE(trailingListenerCalls == 2);
		REQUIRE(addedListenerCalls == 32);
	}

	SECTION("Nested Broadcast defers expired-handle pruning until outer Broadcast completes")
	{
		Delegate<void()> delegate;
		int reentrantListenerCalls = 0;
		int expiredListenerCalls = 0;
		int trailingListenerCalls = 0;
		bool didTriggerNestedBroadcast = false;

		const auto reentrantHandle = delegate.Add([&]()
		{
			++reentrantListenerCalls;
			if (!didTriggerNestedBroadcast)
			{
				didTriggerNestedBroadcast = true;
				delegate.Broadcast();
			}
		});

		auto expiredHandle = std::make_optional(delegate.Add([&](){ ++expiredListenerCalls; }));
		const auto trailingHandle = delegate.Add([&](){ ++trailingListenerCalls; });

		// Expire the middle slot so the inner Broadcast sees an expired weak_ptr;
		// if it pruned mid-outer-loop, the outer loop would skip trailingHandle or read out of bounds.
		expiredHandle.reset();

		delegate.Broadcast();
		REQUIRE(reentrantListenerCalls == 2);
		REQUIRE(expiredListenerCalls == 0);
		REQUIRE(trailingListenerCalls == 2);

		// Confirm expired slot was pruned cleanly once the outer Broadcast exited
		delegate.Broadcast();
		REQUIRE(reentrantListenerCalls == 3);
		REQUIRE(expiredListenerCalls == 0);
		REQUIRE(trailingListenerCalls == 3);
	}

	SECTION("Listener unsubscribing a sibling or itself during Broadcast")
	{
		Delegate<void()> delegate;
		int unsubscriberCalls = 0;
		int siblingCalls = 0;
		int selfUnsubscriberCalls = 0;

		std::optional<DelegateHandle<void()>> siblingHandle;
		std::optional<DelegateHandle<void()>> selfHandle;

		const auto unsubscriberHandle = delegate.Add([&]()
		{
			++unsubscriberCalls;
			siblingHandle.reset();
		});

		siblingHandle = std::make_optional(delegate.Add([&](){ ++siblingCalls; }));

		selfHandle = std::make_optional(delegate.Add([&]()
		{
			++selfUnsubscriberCalls;
			// Destroying own handle mid-callback must keep the lambda alive for the rest of this call
			selfHandle.reset();
		}));

		delegate.Broadcast();
		REQUIRE(unsubscriberCalls == 1);
		REQUIRE(siblingCalls == 0);
		REQUIRE(selfUnsubscriberCalls == 1);

		delegate.Broadcast();
		REQUIRE(unsubscriberCalls == 2);
		REQUIRE(siblingCalls == 0);
		REQUIRE(selfUnsubscriberCalls == 1);
	}
}
