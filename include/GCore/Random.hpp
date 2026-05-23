#pragma once

#include <concepts>
#include <cstdint>
#include <random>

#include "Assert.hpp"

namespace Gadget::Random
{
	using SeedT = std::random_device::result_type;
	using Seed64T = uint64_t;

	// Can be very slow
	// Intended to be used as a seed for a pseudorandom engine
	// Falls back to a time-based seed if hardware entropy fails or is not supported
	SeedT TrueRandomValue() noexcept;

	// Even slower than TrueRandomValue
	// Intended to be used as a seed for a pseudorandom engine
	// Falls back to a time-based seed if hardware entropy fails or is not supported
	Seed64T TrueRandomValue64() noexcept;

	class Engine
	{
	public:
		Engine(SeedT seed = TrueRandomValue()) : internalEngine(seed){}

		// min and max are both inclusive
		template <std::integral T>
		inline T Range(T min, T max)
		{
			auto distribution = std::uniform_int_distribution<T>(min, max);
			return distribution(internalEngine);
		}

		// min and max are both inclusive
		template <std::floating_point T>
		inline T Range(T min, T max)
		{
			auto distribution = std::uniform_real_distribution<T>(min, max);
			return distribution(internalEngine);
		}

	private:
		std::mt19937 internalEngine;
	};
}
