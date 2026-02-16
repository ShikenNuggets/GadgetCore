#pragma once

#include <mutex>
#include <queue>

namespace Gadget
{
	template <class T>
	class ThreadSafeQueue
	{
	public:
		void Push(const T& inValue)
		{
			auto lock = std::lock_guard(queueMutex);
			internalQueue.push(inValue);
		}

		void Push(T&& inValue)
		{
			auto lock = std::lock_guard(queueMutex);
			internalQueue.push(std::move(inValue));
		}

		template <typename... Args>
		void Emplace(Args&&... args)
		{
			auto lock = std::lock_guard(queueMutex);
			internalQueue.emplace(std::forward<Args>(args)...);
		}

		bool Pop(T& outValue)
		{
			auto lock = std::lock_guard(queueMutex);

			if (internalQueue.empty())
			{
				return false;
			}

			outValue = internalQueue.front();
			internalQueue.pop();
			return true;
		}

		bool IsEmpty() const
		{
			auto lock = std::lock_guard(queueMutex);
			return internalQueue.empty();
		}

	private:
		mutable std::mutex queueMutex;
		std::queue<T> internalQueue;
	};
}
