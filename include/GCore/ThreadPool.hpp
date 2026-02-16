#pragma once

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include "ThreadSafeQueue.hpp"

namespace Gadget
{
	class ThreadPool
	{
	public:
		void Start();
		void Stop();
		void QueueJob(const std::function<void()>& job);

		bool IsBusy() const;

	private:
		std::atomic<bool> shouldTerminate = false;
		std::vector<std::thread> threads;
		ThreadSafeQueue<std::function<void()>> jobs;

		void ThreadBusyWait();
	};
}
