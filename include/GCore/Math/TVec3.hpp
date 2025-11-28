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

		static inline constexpr TVec3 Fill(T value) noexcept{ return TVec3(value, value, value); }

		// Sorry for baking in these assumptions, but it's useful
		static inline constexpr TVec3 Up() noexcept{ return TVec3(0.0, 1.0, 0.0); }
		static inline constexpr TVec3 Forward() noexcept{ return TVec3(0.0, 0.0, -1.0); }
		static inline constexpr TVec3 Right() noexcept{ return TVec3(1.0, 0.0, 0.0); }
	};
}