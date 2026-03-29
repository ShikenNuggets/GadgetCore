#pragma once

#include <chrono>

namespace Gadget
{
	class Timer
	{
	public:
		Timer();

		void Update();
		void Reset();

		[[nodiscard]] double DeltaSeconds() const;
		[[nodiscard]] double SecondsSinceLastUpdate() const;
		[[nodiscard]] double SecondsSinceStart() const;

	private:
		std::chrono::microseconds startTick;
		std::chrono::microseconds previousTick;
		std::chrono::microseconds currentTick;

		[[nodiscard]] static inline std::chrono::microseconds GetCurrentTick()
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
		}

		[[nodiscard]] static inline double TicksToSeconds(std::chrono::microseconds ticks)
		{
			return static_cast<double>(ticks.count()) / 1'000'000;
		}
	};
}
