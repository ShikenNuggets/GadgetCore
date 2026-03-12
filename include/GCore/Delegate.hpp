#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "Assert.hpp"

namespace Gadget
{
	template <typename T>
	class DelegateHandle
	{
	public:
		explicit DelegateHandle(std::function<T>&& callback) : func(std::make_shared<std::function<T>>(std::move(callback))){}

		std::weak_ptr<std::function<T>> GetWeakPtr()
		{
			return { func };
		}

	private:
		std::shared_ptr<std::function<T>> func;
	};

	template <typename T>
	class Delegate
	{
	public:
		DelegateHandle<T> Add(std::function<T> callback)
		{
			GADGET_ASSERT(static_cast<bool>(callback), "Tried to bind a std::function with no target");

			auto handle = DelegateHandle<T>(std::move(callback));
			callbacks.push_back(handle.GetWeakPtr());
			return handle;
		}

		template <typename... Args>
		void Broadcast(const Args&... args)
		{
			bool anyInvalid = false;
			for (auto& callbackWeakPtr : callbacks)
			{
				auto callbackPtr = callbackWeakPtr.lock();
				if (callbackPtr == nullptr)
				{
					anyInvalid = true;
					continue;
				}

				(*callbackPtr)(args...);
			}

			if (anyInvalid)
			{
				std::erase_if(callbacks, [](const auto& wp){ return wp.expired(); });
			}
		}

	private:
		std::vector<std::weak_ptr<std::function<T>>> callbacks;
	};
}
