#pragma once

#include "Math.hpp"

namespace Gadget
{
	template <typename T>
	struct TQuat
	{
		T x, y, z, w;

		explicit TQuat(T x_ = 0.0, T y_ = 0.0, T z_ = 0.0, T w_ = 0.0) : x(x_), y(y_), z(z_), w(w_){}
	};

	using Quaternion = TQuat<Math::GFloat>;
}
