#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	// Column Major Order
	// [0][3][6]
	// [1][4][7]
	// [2][5][8]
	template <Math::FloatLike T>
	class TMat3
	{
	public:
		constexpr TMat3() : m{ 1.0, 0.0, 0.0, /**/ 0.0, 1.0, 0.0, /**/ 0.0, 0.0, 1.0}{}

		constexpr TMat3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3) : m{}
		{
			m[0] = a1;
			m[1] = a2;
			m[2] = a3;

			m[3] = b1;
			m[4] = b2;
			m[5] = b3;

			m[6] = c1;
			m[7] = c2;
			m[8] = c3;
		}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

		static inline constexpr TMat3 Identity()
		{
			return TMat3(1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,
				0.0, 0.0, 1.0
			);
		}

	private:
		std::array<T, 3 * 3> m;
	};
}
