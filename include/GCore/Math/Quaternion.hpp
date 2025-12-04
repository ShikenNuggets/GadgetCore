#pragma once

#include "Math.hpp"
#include "TVec3.hpp"

namespace Gadget
{
	template <Math::FloatLike T>
	struct TQuat
	{
		T w, x, y, z;

		explicit constexpr TQuat(T w_ = 1.0, T x_ = 0.0, T y_ = 0.0, T z_ = 0.0) noexcept : w(w_), x(x_), y(y_), z(z_){}

		static inline constexpr TQuat Identity() noexcept{ return TQuat(1.0, 0.0, 0.0, 0.0); }

		inline constexpr TQuat operator*(const TQuat& q) const noexcept
		{
			return TQuat(
				(w * q.w) - (x * q.x) - (y * q.y) - (z * q.z),
				(w * q.x) + (x * q.w) + (y * q.z) - (z * q.y),
				(w * q.y) - (x * q.z) + (y * q.w) + (z * q.x),
				(w * q.z) + (x * q.y) - (y * q.x) + (z * q.w)
			);
		}

		inline constexpr TVec3<T> operator*(const TVec3<T>& vec) const noexcept
		{
			const auto u = TVec3<T>(x, y, z);
			const auto s = w;
			return 2.0 * TVec3<T>::Dot(u, vec) * u + (s * s - TVec3<T>::Dot(u, u)) * vec + 2.0 * s * TVec3<T>::Cross(u, vec);
		}

		inline constexpr void operator *=(const TQuat& q) noexcept{ *this = *this * q; }
	};

	using Quaternion = TQuat<Math::GFloat>;
}
