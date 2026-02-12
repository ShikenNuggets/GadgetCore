#pragma once

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <functional>
#include <ranges>
#include <vector>

#include "Assert.hpp"

namespace Gadget
{
	struct DelegateHandle
	{
		uint64_t id;

		bool operator ==(const DelegateHandle& h2) const{ return id == h2.id; }
	};

	template <typename T>
	struct DelegateCallback
	{
		std::function<T> func;
		DelegateHandle handle;
	};

	template <typename T>
	class Delegate
	{
	public:
		DelegateHandle Add(std::function<T> callback)
		{
			callbacks.emplace_back({ std::move(callback), { lastId++ } });
		}

		void Remove(DelegateHandle handle)
		{
			const auto containsHandle = [handle](const auto& callback){ return callback.handle == handle; };
			GADGET_ASSERT(std::ranges::any_of(callbacks, containsHandle), "Delegate does not contain handle with ID {}", handle.id);
			
			std::erase(callbacks, handle);
		}

		template <typename... Args>
		void Broadcast(const Args&... args)
		{
			for (auto& callback : callbacks)
			{
				if (callback.func)
				{
					callback.func(args...);
				}
			}
		}

	private:
		// Slightly icky but guarantees callback handles will always have unique values
		// 32 bit would probably be adequate, but we'll play it safe and use 64
		// If we made a callback every nanosecond it would take ~584 years for this to overflow
		static inline std::atomic<uint64_t> lastId = 0;

		std::vector<DelegateCallback<T>> callbacks;
		DelegateHandle handle;
	};
}
