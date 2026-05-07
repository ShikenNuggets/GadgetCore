#pragma once

#include <cstdint>
#include <random>

#include "Assert.hpp"

namespace Gadget::Random
{
	using SeedT = std::random_device::result_type;

	// Can be very slow
	// Intended to be used as a seed for a pseudorandom engine
	// Falls back to a time-based seed if hardware entropy fails or is not supported
	SeedT TrueRandomValue();
}
