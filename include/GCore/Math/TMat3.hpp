#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	//Column Major Order
	//[0][3][6]
	//[1][4][7]
	//[2][5][8]
	template <Math::FloatLike T>
	class TMat3
	{
	public:
		constexpr TMat3() : m{ 1.0, 0.0, 0.0, /**/ 0.0, 1.0, 0.0, /**/ 0.0, 0.0, 1.0}{}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

	private:
		std::array<T, 3 * 3> m;
	};
}
