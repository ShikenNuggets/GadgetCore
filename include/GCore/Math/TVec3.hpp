#pragma once

#include "Math.hpp"
#include "TVec2.hpp"

namespace Gadget
{
	template<Math::FloatLike T>
	struct TVec3
	{
		T x, y, z;

		explicit constexpr TVec3(T x_ = 0.0, T y_ = 0.0, T z_ = 0.0) noexcept : x(x_), y(y_), z(z_){}
	};
}