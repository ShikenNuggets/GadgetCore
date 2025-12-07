#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	// Column Major Order
	// [00][04][08][12]
	// [01][05][09][13]
	// [02][06][10][14]
	// [03][07][11][15]
	template <Math::FloatLike T>
	class TMat4
	{
	public:
		constexpr TMat4() : m{ 1.0, 0.0, 0.0, 0.0, /**/ 0.0, 1.0, 0.0, 0.0, /**/ 0.0, 0.0, 1.0, 0.0, /**/ 0.0, 0.0, 0.0, 1.0 }{}
		
		constexpr TMat4(T a1, T a2, T a3, T a4, T b1, T b2, T b3, T b4, T c1, T c2, T c3, T c4, T d1, T d2, T d3, T d4) : m{}
		{
			m[0] = a1;
			m[1] = a2;
			m[2] = a3;
			m[3] = a4;

			m[4] = b1;
			m[5] = b2;
			m[6] = b3;
			m[7] = b4;

			m[8] = c1;
			m[9] = c2;
			m[10] = c3;
			m[11] = c4;

			m[12] = d1;
			m[13] = d2;
			m[14] = d3;
			m[15] = d4;
		}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

		static inline constexpr TMat4 Identity()
		{
			return TMat4(1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0
			);
		}

	private:
		std::array<T, 4 * 4> m;
	};
}
