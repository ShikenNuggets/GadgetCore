#pragma once

#include <cstdint>

namespace Gadget
{
	struct ScreenCoordinate
	{
		int32_t x, y; // 16 bits is realistically adequate for all real-world use-cases, but a hypothetical ultrawide 16K monitor would get dangerously close to the limit

		explicit constexpr ScreenCoordinate(int32_t x_, int32_t y_) noexcept : x(x_), y(y_){}
	};
}
