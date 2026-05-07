#include "Random.hpp"

#include "Logger.hpp"

using namespace Gadget;

Random::SeedT Random::TrueRandomValue()
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
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
