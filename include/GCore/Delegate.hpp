#pragma once

#include <functional>
#include <vector>
#include <utility>

namespace Gadget
{
	template <typename T>
	class Delegate
	{
	public:
		using CallbackType = std::function<T>;

		void Add(CallbackType callback)
		{
			callbacks.emplace_back(std::move(callback));
		}

		template <typename... Args>
		void Broadcast(const Args&... args)
		{
			for (auto& callback : callbacks)
			{
				if (callback)
				{
					callback(args...);
				}
			}
		}

	private:
		std::vector<CallbackType> callbacks;
	};
}
