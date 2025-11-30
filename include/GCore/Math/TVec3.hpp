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

		static inline constexpr TVec3 Zero() noexcept{ return TVec3(0.0, 0.0, 0.0); }
		static inline constexpr TVec3 Fill(T value) noexcept{ return TVec3(value, value, value); }

		inline constexpr TVec3 operator-() const noexcept{ return TVec3(-x, -y, -z); }
		inline constexpr TVec3 operator+(const TVec3& v) const noexcept{ return TVec3(x + v.x, y + v.y, z + v.z); }
		inline constexpr TVec3 operator-(const TVec3& v) const noexcept{ return TVec3(x - v.x, y - v.y, z - v.z); }
		inline constexpr TVec3 operator*(T v) const noexcept{ return TVec3(x * v, y * v, z * v); }
		inline constexpr TVec3 operator/(T v) const noexcept{ return TVec3(Math::SafeDivide(x, v), Math::SafeDivide(y, v), Math::SafeDivide(z, v)); }

		friend inline constexpr TVec3 operator*(T s, const TVec3& v){ return v * s; }

		inline constexpr void operator+=(const TVec3& v) noexcept{ *this = *this + v; }
		inline constexpr void operator-=(const TVec3& v) noexcept{ *this = *this - v; }
		inline constexpr void operator*=(T v) noexcept{ *this = *this * v; }
		inline constexpr void operator/=(T v) noexcept{ *this = *this / v; }

		inline constexpr T SquaredMagnitude() const noexcept{ return (x * x) + (y * y) + (z * z); }
		inline T Magnitude() const{ return Math::Sqrt(SquaredMagnitude()); }
		inline TVec3 Normal() const{ return *this / Magnitude(); }
		inline void Normalize(){ *this = Normal(); }

		static inline constexpr T Dot(const TVec3& a, const TVec3& b) noexcept{ return Math::Dot3D(a.x, a.y, a.z, b.x, b.y, b.z); }

		static inline constexpr TVec3 Cross(const TVec3& a, const TVec3& b) noexcept
		{
			return TVec3(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			);
		}

		static inline constexpr TVec3 Lerp(const TVec3& a, const TVec3& b, T t) noexcept{ return a + t * (b - a); }

		// Sorry for baking in these assumptions, but it's useful
		static inline constexpr TVec3 Up() noexcept{ return TVec3(0.0, 1.0, 0.0); }
		static inline constexpr TVec3 Forward() noexcept{ return TVec3(0.0, 0.0, -1.0); }
		static inline constexpr TVec3 Right() noexcept{ return TVec3(1.0, 0.0, 0.0); }

		inline constexpr bool IsNear(const TVec3& value) const noexcept{ return Math::IsNear(x, value.x) && Math::IsNear(y, value.y) && Math::IsNear(z, value.z); }
		inline constexpr bool IsValid() const{ return Math::IsValidNumber(x) && Math::IsValidNumber(y) && Math::IsValidNumber(z); }
	};
}