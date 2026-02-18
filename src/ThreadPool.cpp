#include "ThreadPool.hpp"

#include <algorithm>

#include "Assert.hpp"

using namespace Gadget;

void ThreadPool::Start()
{
	size_t numThreadsToSpawn = 1;

	auto numHardwareThreads = std::thread::hardware_concurrency();
	if (numHardwareThreads > 1)
	{
		numThreadsToSpawn = numHardwareThreads - 1;
	}
	
	Start(numThreadsToSpawn);
}

void ThreadPool::Start(size_t numThreads)
{
	shouldTerminate = false;
	
	GADGET_BASIC_ASSERT(numThreads > 0);
	numThreads = std::max<size_t>(numThreads, 1);
	for (size_t i = 0; i < numThreads; i++)
	{
		threads.emplace_back(&ThreadPool::ThreadBusyWait, this);
	}
}

void ThreadPool::Stop()
{
	shouldTerminate = true;
	for (auto& thread : threads)
	{
		thread.join();
	}

	threads.clear();
}

void ThreadPool::QueueJob(const std::function<void()>& job)
{
	jobs.Push(job);
}

bool ThreadPool::IsBusy() const
{
	return !jobs.IsEmpty();
}

void ThreadPool::ThreadBusyWait()
{
	while (true)
	{
		if (shouldTerminate)
		{
			return;
		}

		std::function<void()> job;
		if (jobs.Pop(job))
		{
			job();
		}
	}
}
