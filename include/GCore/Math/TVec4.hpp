#pragma once

#include "Math.hpp"
#include "TVec2.hpp"
#include "TVec3.hpp"

namespace Gadget
{
	template<Math::FloatLike T>
	struct TVec4
	{
		T x, y, z, w;

		explicit constexpr TVec4(T x_ = 0.0, T y_ = 0.0, T z_ = 0.0, T w_ = 0.0) noexcept : x(x_), y(y_), z(z_), w(w_){}

		static inline constexpr TVec4 Fill(T value) noexcept{ return TVec4(value, value, value, value); }

		inline constexpr TVec4 operator+(const TVec4& v) const noexcept{ return TVec4(x + v.x, y + v.y, z + v.z, w + v.w); }
		inline constexpr TVec4 operator*(T v) const noexcept{ return TVec4(x * v, y * v, z * v, w * v); }

		friend inline constexpr TVec4 operator*(T s, const TVec4& v){ return v * s; }

		inline constexpr void operator+=(const TVec4& v) noexcept{ *this = *this + v; }
		inline constexpr void operator*=(T v) noexcept{ *this = *this * v; }

		static inline constexpr T Dot(const TVec4& a, const TVec4& b) noexcept{ return Math::Dot4D(a.x, a.y, a.z, a.w, b.x, b.y, b.z, b.w); }

		inline constexpr bool IsValid() const{ return Math::IsValidNumber(x) && Math::IsValidNumber(y) && Math::IsValidNumber(z) && Math::IsValidNumber(w); }
	};
}