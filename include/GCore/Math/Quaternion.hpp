#pragma once

#include "Math.hpp"

namespace Gadget
{
	template <typename T>
	struct TQuat
	{
		T w, x, y, z;

		explicit constexpr TQuat(T w_ = 1.0, T x_ = 0.0, T y_ = 0.0, T z_ = 0.0) noexcept : w(w_), x(x_), y(y_), z(z_){}

		static inline constexpr TQuat Identity() noexcept{ return TQuat(1.0, 0.0, 0.0, 0.0); }
	};

	using Quaternion = TQuat<Math::GFloat>;
}
