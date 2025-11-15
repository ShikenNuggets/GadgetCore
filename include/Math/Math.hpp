#pragma once

#include <numbers>

namespace GCore::Math
{
	template<typename T>
	concept FloatLike = std::is_floating_point_v<T> && std::is_convertible_v<T, double>;

	using GFloat = double;
	static_assert(FloatLike<float>, "Sanity Check - Built-in float must satisfy the FloatLike concept");
	static_assert(FloatLike<double>, "Sanity Check - Built-in double must satisfy the FloatLike concept");
	static_assert(FloatLike<long double>, "Sanity Check - Built-in long double must satisfy the FloatLike concept");
	static_assert(FloatLike<GFloat>, "GFloat must be a floating point type and implicitly-convertible to double");

	template<FloatLike T>
	static constexpr T TPi = std::numbers::pi_v<T>;
	static constexpr GFloat Pi = TPi<GFloat>;

	template<FloatLike T>
	static constexpr T TNearZero = std::numeric_limits<T>::denorm_min();
	static constexpr GFloat NearZero = TNearZero<GFloat>;

	template<FloatLike T>
	static constexpr T TInfinity = std::numeric_limits<T>::infinity();
	static constexpr GFloat Infinity = TInfinity<GFloat>;

	template<FloatLike T>
	static inline constexpr bool IsNearZero(T value_){ return value_ <= TNearZero<T> && value_ >= -TNearZero<T>; }

	template <FloatLike T>
	static inline constexpr bool IsNear(T a_, T b_){ return IsNearZero(a_ - b_); }

	template <FloatLike T>
	static inline constexpr T SafeDivide(T a_, T b_)
	{
		if (IsNearZero(b_))
		{
			return 0.0;
		}

		return a_ / b_;
	}
}