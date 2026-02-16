#include "ThreadPool.hpp"

using namespace Gadget;

void ThreadPool::Start()
{
	const auto numHardwareThreads = std::thread::hardware_concurrency();
	for (size_t i = 0; i < numHardwareThreads; i++)
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
	return jobs.IsEmpty();
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
		if (!jobs.Pop(job))
		{
			job();
		}
	}
}
