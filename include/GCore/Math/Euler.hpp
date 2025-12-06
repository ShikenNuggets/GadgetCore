#pragma once

#include "Math.hpp"
#include "Vector.hpp"

namespace Gadget
{
	template <Math::FloatLike T>
	struct TEuler
	{
		T x, y, z;

		explicit constexpr TEuler(T x_ = 0.0, T y_ = 0.0, T z_ = 0.0) noexcept : x(x_), y(y_), z(z_){}
		explicit TEuler(const TVec3<T>& v) noexcept : x(v.x), y(v.y), z(v.z){}
	};

	using Euler = TEuler<Math::GFloat>;
}