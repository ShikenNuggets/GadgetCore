#pragma once

#include <numbers>

namespace GCore::Math
{
	template<typename T>
	concept FloatLike = std::is_floating_point_v<T> && std::is_convertible_v<T, double>;

	using GFloat = double;
	static_assert(FloatLike<GFloat>, "GFloat must be a floating point type and implicitly-convertible to double");

	static constexpr GFloat Pi = std::numbers::pi_v<GFloat>;
	static constexpr GFloat NearZero = std::numeric_limits<GFloat>::denorm_min();
	static constexpr GFloat Infinity = std::numeric_limits<GFloat>::infinity();

	template<FloatLike T>
	static inline constexpr bool IsNearZero(T value_){ return value_ <= NearZero && value_ >= -NearZero; }

	template <FloatLike T>
	static inline constexpr bool IsNear(T a_, T b_){ return IsNearZero(a_ - b_); }

	template <FloatLike T>
	static inline constexpr T SafeDivide(T a_, T b_)
	{
		if (IsNearZero(b_))
		{
			return 0;
		}

		return a_ / b_;
	}
}