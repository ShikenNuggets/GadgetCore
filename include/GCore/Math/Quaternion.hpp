#pragma once

#include "CoreMath.hpp"
#include "TVec3.hpp"

namespace Gadget
{
	template <Math::FloatLike T>
	struct TQuat
	{
		T w, x, y, z;

		explicit constexpr TQuat(T w_ = 1.0, T x_ = 0.0, T y_ = 0.0, T z_ = 0.0) noexcept : w(w_), x(x_), y(y_), z(z_){}

		[[nodiscard]] static inline constexpr TQuat Identity() noexcept{ return TQuat(1.0, 0.0, 0.0, 0.0); }

		[[nodiscard]] inline constexpr TQuat operator-() const noexcept{ return TQuat(-w, -x, -y, -z); }
		[[nodiscard]] inline constexpr TQuat operator+(const TQuat& q) const noexcept{ return TQuat(w + q.w, x + q.x, y + q.y, z + q.z); }

		[[nodiscard]] inline constexpr TQuat operator*(const TQuat& q) const noexcept
		{
			return TQuat(
				(w * q.w) - (x * q.x) - (y * q.y) - (z * q.z),
				(w * q.x) + (x * q.w) + (y * q.z) - (z * q.y),
				(w * q.y) - (x * q.z) + (y * q.w) + (z * q.x),
				(w * q.z) + (x * q.y) - (y * q.x) + (z * q.w)
			);
		}

		[[nodiscard]] inline constexpr TVec3<T> operator*(const TVec3<T>& vec) const noexcept
		{
			const auto u = TVec3<T>(x, y, z);
			const auto s = w;
			return 2.0 * TVec3<T>::Dot(u, vec) * u + (s * s - TVec3<T>::Dot(u, u)) * vec + 2.0 * s * TVec3<T>::Cross(u, vec);
		}

		[[nodiscard]] inline constexpr TQuat operator*(T v) const noexcept{ return TQuat(w * v, x * v, y * v, z * v); }
		[[nodiscard]] inline constexpr TQuat operator/(T v) const noexcept
		{
			return TQuat(Math::SafeDivide(w, v), Math::SafeDivide(x, v), Math::SafeDivide(y, v), Math::SafeDivide(z, v));
		}

		[[nodiscard]] friend inline constexpr TQuat operator*(T s, const TQuat& q) noexcept{ return q * s; }

		inline constexpr void operator *=(const TQuat& q) noexcept{ *this = *this * q; }
		inline constexpr void operator *=(T v) noexcept{ *this = *this * v; }
		inline constexpr void operator /=(T v) noexcept{ *this = *this / v; }

		[[nodiscard]] inline constexpr T SquaredMagnitude() const noexcept{ return (w * w) + (x * x) + (y * y) + (z * z); }
		[[nodiscard]] inline T Magnitude() const{ return Math::Sqrt(SquaredMagnitude()); }
		[[nodiscard]] inline TQuat Normal() const{ return *this / Magnitude(); }
		inline void Normalize(){ *this = Normal(); }

		[[nodiscard]] static inline constexpr T Dot(const TQuat& a, const TQuat& b) noexcept
		{
			return Math::Dot4D(/*A*/ a.w, a.x, a.y, a.z, /*B*/ b.w, b.x, b.y, b.z);
		}

		[[nodiscard]] static inline constexpr TQuat Lerp(const TQuat& q1, const TQuat& q2, T t) noexcept
		{
			if (Dot(q1, q2) < 0.0)
			{
				return (q1 * (1.0 - t) + -q2 * t).Normal();
			}

			return (q1 * (1.0 - t) + q2 * t).Normal();
		}

		[[nodiscard]] inline constexpr bool IsNear(const TQuat& value) const noexcept{ return Math::IsNear(w, value.w) && Math::IsNear(x, value.x) && Math::IsNear(y, value.y) && Math::IsNear(z, value.z); }
		[[nodiscard]] inline constexpr bool IsValid() const{ return Math::IsValidNumber(w) && Math::IsValidNumber(x) && Math::IsValidNumber(y) && Math::IsValidNumber(z); }
	};

	using Quaternion = TQuat<Math::GFloat>;
}
