#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	//Column Major Order
	//[00][04][08][12]
	//[01][05][09][13]
	//[02][06][10][14]
	//[03][07][11][15]
	template <Math::FloatLike T>
	class TMat4
	{
	public:
		constexpr TMat4() : m{ 1.0, 0.0, 0.0, 0.0, /**/ 0.0, 1.0, 0.0, 0.0, /**/ 0.0, 0.0, 1.0, 0.0, /**/ 0.0, 0.0, 0.0, 1.0 }{}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

	private:
		std::array<T, 4 * 4> m;
	};
}
