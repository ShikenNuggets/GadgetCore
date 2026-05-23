#include "Random.hpp"

#include "Logger.hpp"

using namespace Gadget;

Random::SeedT Random::TrueRandomValue() noexcept
{
#ifdef GADGET_PLATFORM_SUPPORTS_RANDOM_DEVICE
	try
	{
		std::random_device rd;
		return rd();
	}
	catch (const std::exception& e)
	{
		GADGET_LOG_ERROR("std::random_device failed to generate a true random value. Error: {}", e.what());
	}
#endif //GADGET_PLATFORM_SUPPORTS_RANDOM_DEVICE

	// Fall back to time-based seed if hardware doesn't support random_device
	auto nanoTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	static_assert(sizeof(nanoTime) >= 8); // Sanity check: the following code is UB if this was ever not true
	return static_cast<Random::SeedT>(nanoTime ^ (nanoTime >> 32)); // This ensures we use every bit from the timestamp even though the result is 32 bit
}

Random::Seed64T Random::TrueRandomValue64() noexcept
{
#ifdef GADGET_PLATFORM_SUPPORTS_RANDOM_DEVICE
	try
	{
		std::random_device rd;
		return (static_cast<uint64_t>(rd()) << 32) | rd();
	}
	catch (const std::exception& e)
	{
		GADGET_LOG_ERROR("std::random_device failed to generate a true random value. Error: {}", e.what());
	}
#endif //GADGET_PLATFORM_SUPPORTS_RANDOM_DEVICE

	// Fall back to time-based seed if hardware doesn't support random_device
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
