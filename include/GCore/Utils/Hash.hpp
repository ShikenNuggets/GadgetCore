#pragma once

#include <cstdint>
#include <string_view>

namespace Gadget::Hash
{
	constexpr uint64_t fnv1a_64_prime = 0x100000001b3;
	constexpr uint64_t fnv1a_64_basis = 0xcbf29ce484222325;

	// FNV1-a
	// O(n) on string length, O(1) spatial complexity
	// Very fast for small strings. Effectiveness drops off around 64 characters
	// Susceptible to hash flooding, avoid using with untrusted inputs
	[[nodiscard]] constexpr uint64_t FastHash64(std::string_view str) noexcept
	{
		uint64_t hash = fnv1a_64_basis;
		for (const auto& c : str)
		{
			hash ^= static_cast<uint64_t>(static_cast<uint8_t>(c));
			hash *= fnv1a_64_prime;
		}

		return hash;
	}
}
