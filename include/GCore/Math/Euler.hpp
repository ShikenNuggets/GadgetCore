#pragma once

#include "CoreMath.hpp"
#include "Vector.hpp"

namespace Gadget
{
	template <Math::FloatLike T>
	struct TEuler
	{
		T x, y, z;

		explicit constexpr TEuler(T x_ = 0.0, T y_ = 0.0, T z_ = 0.0) noexcept : x(x_), y(y_), z(z_){}
		explicit TEuler(const TVec3<T>& v) noexcept : x(v.x), y(v.y), z(v.z){}

		inline constexpr TEuler operator+(const TEuler& e) const noexcept{ return TEuler(x + e.x, y + e.y, z + e.z); }
		inline constexpr TEuler operator-(const TEuler& e) const noexcept{ return TEuler(x - e.x, y - e.y, z - e.z); }
		inline constexpr TEuler operator*(T value) const noexcept{ return TEuler(x * value, y * value, z * value); }

		inline friend constexpr TEuler operator*(float value, const TEuler& e) noexcept{ return e * value; }

		static inline constexpr TEuler Lerp(const TEuler& a, const TEuler& b, T t){ return a + t * (b - a); }

		inline constexpr bool IsValid() const{ return Math::IsValidNumber(x) && Math::IsValidNumber(y) && Math::IsValidNumber(z); }
	};

	using Euler = TEuler<Math::GFloat>;
}