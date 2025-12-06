#pragma once

#include "CoreMath.hpp"

namespace Gadget
{
	template<Math::FloatLike T>
	struct TVec2
	{
		T x, y;

		explicit constexpr TVec2(T x_ = 0.0, T y_ = 0.0) noexcept : x(x_), y(y_){}

		static inline constexpr TVec2 Zero() noexcept{ return TVec2(0.0, 0.0); }
		static inline constexpr TVec2 Fill(T value_) noexcept{ return TVec2(value_, value_); }

		inline constexpr TVec2 operator -() const noexcept{ return TVec2(-x, -y); }
		inline constexpr TVec2 operator +(const TVec2& value_) const noexcept{ return TVec2(x + value_.x, y + value_.y); }
		inline constexpr TVec2 operator -(const TVec2& value_) const noexcept{ return TVec2(x - value_.x, y - value_.y); }
		inline constexpr TVec2 operator *(T value_) const noexcept{ return TVec2(x * value_, y * value_); }
		inline constexpr TVec2 operator /(T value_) const noexcept{ return TVec2(Math::SafeDivide(x, value_), Math::SafeDivide(y, value_)); }

		friend inline constexpr TVec2 operator *(T s, const TVec2& v){ return v * s; }

		inline constexpr void operator +=(const TVec2& v) noexcept{ *this = *this + v; }
		inline constexpr void operator -=(const TVec2& v) noexcept{ *this = *this - v; }
		inline constexpr void operator *=(T v) noexcept{ *this = *this * v; }
		inline constexpr void operator /=(T v) noexcept{ *this = *this / v; }

		inline constexpr T SquaredMagnitude() const noexcept{ return (x * x) + (y * y); }
		inline T Magnitude() const{ return Math::Sqrt(SquaredMagnitude()); }
		inline TVec2 Normal() const{ return *this / Magnitude(); }
		inline void Normalize(){ *this = Normal(); }

		static inline constexpr T Dot(const TVec2& a, const TVec2& b) noexcept{ return Math::Dot2D(a.x, a.y, b.x, b.y); }
		static inline constexpr TVec2 Lerp(const TVec2& a, const TVec2& b, T t) noexcept{ return a + t * (b - a); }

		inline constexpr bool IsNear(const TVec2& value) const noexcept{ return Math::IsNear(x, value.x) && Math::IsNear(y, value.y); }
		inline constexpr bool IsValid() const{ return Math::IsValidNumber(x) && Math::IsValidNumber(y); }
	};
}