#pragma once

#include <cstdint>
#include <string_view>

#include "GCore/Random.hpp"

namespace Gadget::Hash
{
	namespace Internal
	{
		constexpr uint32_t fnv1a_32_prime = 0x1000193;
		constexpr uint32_t fnv1a_32_basis = 0x811c9dc5;

		constexpr uint64_t fnv1a_64_prime = 0x100000001b3;
		constexpr uint64_t fnv1a_64_basis = 0xcbf29ce484222325;
	}

	// FNV1-a
	// Very fast for small strings. Effectiveness drops off around 64 characters
	// Susceptible to hash flooding, avoid using with untrusted inputs
	// Relatively high risk of collision, prefer 64-bit
	[[nodiscard]] constexpr uint32_t FastHash32(std::string_view str) noexcept
	{
		uint32_t hash = Internal::fnv1a_32_basis;
		for(const auto& c : str)
		{
			hash ^= static_cast<uint64_t>(static_cast<uint8_t>(c));
			hash *= Internal::fnv1a_32_prime;
		}

		return hash;
	}

	// FNV1-a
	// O(n) on string length, O(1) spatial complexity
	// Very fast for small strings. Effectiveness drops off around 64 characters
	// Susceptible to hash flooding, avoid using with untrusted inputs
	[[nodiscard]] constexpr uint64_t FastHash64(std::string_view str) noexcept
	{
		uint64_t hash = Internal::fnv1a_64_basis;
		for (const auto& c : str)
		{
			hash ^= static_cast<uint64_t>(static_cast<uint8_t>(c));
			hash *= Internal::fnv1a_64_prime;
		}

		return hash;
	}

	struct SipKey
	{
		Random::Seed64T k0;
		Random::Seed64T k1;

		[[nodiscard]] static inline SipKey GenerateTrueRandomKey()
		{
			return SipKey
			{
				.k0 = Random::TrueRandomValue64(),
				.k1 = Random::TrueRandomValue64()
			};
		}
	};

	namespace Internal
	{
		[[nodiscard]] constexpr uint64_t RotateLeft(uint64_t x, int b) noexcept
		{
			return (x << b) | (x >> (64 - b));
		}

		struct SipState
		{
			uint64_t v0;
			uint64_t v1;
			uint64_t v2;
			uint64_t v3;

			explicit constexpr SipState(const SipKey& key)
			{
				v0 = 0x736f6d6570736575ULL ^ key.k0;
				v1 = 0x646f6d616e646f62ULL ^ key.k1;
				v2 = 0x6c65746574656462ULL ^ key.k0;
				v3 = 0x7465737464726976ULL ^ key.k1;
			}

			constexpr void SipRound()
			{
				v0 += v1;
				v1 = RotateLeft(v1, 13);
				v1 ^= v0;
				v0 = RotateLeft(v0, 32);

				v2 += v3;
				v3 = RotateLeft(v3, 16);
				v3 ^= v2;

				v0 += v3;
				v3 = RotateLeft(v3, 21);
				v3 ^= v0;

				v2 += v1;
				v1 = RotateLeft(v1, 17);
				v1 ^= v2;
				v2 = RotateLeft(v2, 32);
			}
		};
	}

	// SipHash 2.4
	// 3-5x slower than FastHash64 for small strings, but faster at > 64 characters
	// Not truly cryptographically secure, but as good as it gets for a fast 64-bit output
	// Resistant to hash flooding when a secret/random key is used
	[[nodiscard]] constexpr uint64_t SafeHash64(std::string_view str, SipKey key) noexcept
	{
		auto state = Internal::SipState(key);

		const auto len = str.size();
		const auto blocks = len / 8;
		const auto left = len % 8;

		for (size_t i = 0; i < blocks; i++)
		{
			uint64_t m = 0;
			for (auto j = 0; j < 8; j++)
			{
				m |= static_cast<uint64_t>(static_cast<unsigned char>(str[i * 8 + j])) << (j * 8);
			}

			state.v3 ^= m;
			state.SipRound();
			state.SipRound();
			state.v0 ^= m;
		}

		uint64_t b = static_cast<uint64_t>(len) << 56;
		for (size_t i = 0; i < left; i++)
		{
			b |= static_cast<uint64_t>(static_cast<unsigned char>(str[blocks * 8 + i])) << (i * 8);
		}

		state.v3 ^= b;
		state.SipRound();
		state.SipRound();
		state.v0 ^= b;

		state.v2 ^= 0xff;
		state.SipRound();
		state.SipRound();
		state.SipRound();
		state.SipRound();

		return state.v0 ^ state.v1 ^ state.v2 ^ state.v3;
	}
}
