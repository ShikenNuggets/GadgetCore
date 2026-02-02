#pragma once

#include "CoreMath.hpp"

namespace Gadget
{
	template<Math::FloatLike T>
	struct TVec2
	{
		T x, y;

		explicit constexpr TVec2(T x_ = 0.0, T y_ = 0.0) noexcept : x(x_), y(y_){}

		[[nodiscard]] static inline constexpr TVec2 Zero() noexcept{ return TVec2(0.0, 0.0); }
		[[nodiscard]] static inline constexpr TVec2 Fill(T value_) noexcept{ return TVec2(value_, value_); }

		[[nodiscard]] inline constexpr TVec2 operator -() const noexcept{ return TVec2(-x, -y); }
		[[nodiscard]] inline constexpr TVec2 operator +(const TVec2& value_) const noexcept{ return TVec2(x + value_.x, y + value_.y); }
		[[nodiscard]] inline constexpr TVec2 operator -(const TVec2& value_) const noexcept{ return TVec2(x - value_.x, y - value_.y); }
		[[nodiscard]] inline constexpr TVec2 operator *(T value_) const noexcept{ return TVec2(x * value_, y * value_); }
		[[nodiscard]] inline constexpr TVec2 operator /(T value_) const noexcept{ return TVec2(Math::SafeDivide(x, value_), Math::SafeDivide(y, value_)); }

		[[nodiscard]] friend inline constexpr TVec2 operator *(T s, const TVec2& v){ return v * s; }

		inline constexpr void operator +=(const TVec2& v) noexcept{ *this = *this + v; }
		inline constexpr void operator -=(const TVec2& v) noexcept{ *this = *this - v; }
		inline constexpr void operator *=(T v) noexcept{ *this = *this * v; }
		inline constexpr void operator /=(T v) noexcept{ *this = *this / v; }

		[[nodiscard]] inline constexpr T SquaredMagnitude() const noexcept{ return (x * x) + (y * y); }
		[[nodiscard]] inline T Magnitude() const{ return Math::Sqrt(SquaredMagnitude()); }
		[[nodiscard]] inline TVec2 Normal() const{ return *this / Magnitude(); }
		inline void Normalize(){ *this = Normal(); }

		[[nodiscard]] static inline constexpr T Dot(const TVec2& a, const TVec2& b) noexcept{ return Math::Dot2D(a.x, a.y, b.x, b.y); }
		[[nodiscard]] static inline constexpr TVec2 Lerp(const TVec2& a, const TVec2& b, T t) noexcept{ return a + t * (b - a); }
		[[nodiscard]] static inline constexpr T Determinant(const TVec2& a, const TVec2& b) noexcept{ return (a.x * b.y) - (a.y * b.x); }

		[[nodiscard]] inline constexpr bool IsNear(const TVec2& value) const noexcept{ return Math::IsNear(x, value.x) && Math::IsNear(y, value.y); }
		[[nodiscard]] inline constexpr bool IsValid() const{ return Math::IsValidNumber(x) && Math::IsValidNumber(y); }
	};
}