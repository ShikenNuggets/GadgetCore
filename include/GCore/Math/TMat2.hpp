#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	// Column Major Order
	// [0][2]
	// [1][3]
	template <Math::FloatLike T>
	class TMat2
	{
	public:
		constexpr TMat2() : m{ 1.0, 0.0, 0.0, 1.0 }{}

		constexpr TMat2(T a1, T a2, T b1, T b2) : m{}
		{
			m[0] = a1;
			m[1] = a2;

			m[2] = b1;
			m[3] = b2;
		}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

		static inline constexpr TMat2 Identity()
		{
			return TMat2(1.0, 0.0,
				0.0, 1.0
			);
		}

	private:
		std::array<T, 2 * 2> m;
	};
}
