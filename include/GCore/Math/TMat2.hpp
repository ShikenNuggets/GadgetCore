#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	//Column Major Order
	//[0][2]
	//[1][3]
	template <Math::FloatLike T>
	class TMat2
	{
	public:
		constexpr TMat2() : m{ 1.0, 0.0, 0.0, 1.0 }{}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

	private:
		std::array<T, 2 * 2> m;
	};
}
