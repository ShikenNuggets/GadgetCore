#pragma once

#include "CoreMath.hpp"
#include "TVec2.hpp"
#include "TVec3.hpp"

namespace Gadget
{
	template<Math::FloatLike T>
	struct TVec4
	{
		T x, y, z, w;

		explicit constexpr TVec4(T x_ = 0.0, T y_ = 0.0, T z_ = 0.0, T w_ = 0.0) noexcept : x(x_), y(y_), z(z_), w(w_){}

		[[nodiscard]] static inline constexpr TVec4 Zero() noexcept{ return TVec4(0.0, 0.0, 0.0, 0.0); }
		[[nodiscard]] static inline constexpr TVec4 Fill(T value) noexcept{ return TVec4(value, value, value, value); }

		[[nodiscard]] inline constexpr TVec4 operator-() const noexcept{ return TVec4(-x, -y, -z, -w); }
		[[nodiscard]] inline constexpr TVec4 operator+(const TVec4& v) const noexcept{ return TVec4(x + v.x, y + v.y, z + v.z, w + v.w); }
		[[nodiscard]] inline constexpr TVec4 operator-(const TVec4& v) const noexcept{ return TVec4(x - v.x, y - v.y, z - v.z, w - v.w); }
		[[nodiscard]] inline constexpr TVec4 operator*(T v) const noexcept{ return TVec4(x * v, y * v, z * v, w * v); }
		[[nodiscard]] inline constexpr TVec4 operator/(T v) const noexcept{ return TVec4(Math::SafeDivide(x, v), Math::SafeDivide(y, v), Math::SafeDivide(z, v), Math::SafeDivide(w, v)); }

		[[nodiscard]] friend inline constexpr TVec4 operator*(T s, const TVec4& v){ return v * s; }

		inline constexpr void operator+=(const TVec4& v) noexcept{ *this = *this + v; }
		inline constexpr void operator-=(const TVec4& v) noexcept{ *this = *this - v; }
		inline constexpr void operator*=(T v) noexcept{ *this = *this * v; }
		inline constexpr void operator/=(T v) noexcept{ *this = *this / v; }

		[[nodiscard]] inline constexpr T SquaredMagnitude() const noexcept{ return (x * x) + (y * y) + (z * z) + (w * w); }
		[[nodiscard]] inline T Magnitude() const{ return Math::Sqrt(SquaredMagnitude()); }
		[[nodiscard]] inline TVec4 Normal() const{ return *this / Magnitude(); }
		inline void Normalize(){ *this = Normal(); }

		[[nodiscard]] static inline constexpr T Dot(const TVec4& a, const TVec4& b) noexcept{ return Math::Dot4D(a.x, a.y, a.z, a.w, b.x, b.y, b.z, b.w); }
		[[nodiscard]] static inline constexpr TVec4 Lerp(const TVec4& a, const TVec4& b, T t) noexcept{ return a + t * (b - a); }

		[[nodiscard]] inline constexpr bool IsNear(const TVec4& value) const noexcept{ return Math::IsNear(x, value.x) && Math::IsNear(y, value.y) && Math::IsNear(z, value.z) && Math::IsNear(w, value.w); }
		[[nodiscard]] inline constexpr bool IsValid() const{ return Math::IsValidNumber(x) && Math::IsValidNumber(y) && Math::IsValidNumber(z) && Math::IsValidNumber(w); }
	};
}