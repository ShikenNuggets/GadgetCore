#pragma once

#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>
#include <type_traits>

namespace GCore::Math
{
	template<typename T>
	concept FloatLike = std::is_floating_point_v<T> && std::is_convertible_v<T, double>;
	static_assert(FloatLike<float>, "Sanity Check - Built-in float must satisfy the FloatLike concept");
	static_assert(FloatLike<double>, "Sanity Check - Built-in double must satisfy the FloatLike concept");
	static_assert(FloatLike<long double>, "Sanity Check - Built-in long double must satisfy the FloatLike concept");

	template <typename T>
	concept Numeric = std::is_arithmetic_v<T> and not std::is_same_v<T, bool> and not std::is_same_v<T, char> and not std::is_same_v<T, wchar_t>;
	static_assert(Numeric<int>, "Sanity Check - int must satisfy the Numeric concept");
	static_assert(Numeric<int8_t>, "Sanity Check - int8_t must satisfy the Numeric concept");
	static_assert(Numeric<uint8_t>, "Sanity Check - uint8_t must satisfy the Numeric concept");
	static_assert(Numeric<uint64_t>, "Sanity Check - uint64_t must satisfy the Numeric concept");
	static_assert(Numeric<float>, "Sanity Check - float must satisfy the Numeric concept");
	static_assert(!Numeric<bool>, "Sanity Check - bool is not numeric");
	static_assert(!Numeric<char>, "Sanity Check - char should not be used as a numeric type");
	static_assert(!Numeric<wchar_t>, "Sanity Check - wchar_t should not be used as a numeric type");

	using GFloat = double;
	static_assert(Numeric<GFloat>, "GFloat must be numeric type");
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

	static constexpr uint64_t LargestPrime = 18'446'744'073'709'551'557ULL; //Largest prime number that can be represented by a 64 bit integer

	template <FloatLike T>
	static inline constexpr bool IsValidNumber(T value)
	{
		return !std::isnan(value) && !std::isinf(value);
	}

	template <Numeric T>
	static inline T Sqrt(T value)
	{
		// TODO - constexpr in C++26
		return std::sqrt(value);
	}

	template<FloatLike T>
	static inline constexpr bool IsNearZero(T value_) noexcept{ return value_ <= TNearZero<T> && value_ >= -TNearZero<T>; }

	template <FloatLike T>
	static inline constexpr bool IsNear(T a_, T b_) noexcept{ return IsNearZero(a_ - b_); }

	template <FloatLike T>
	static inline constexpr T SafeDivide(T a_, T b_) noexcept
	{
		if (IsNearZero(b_))
		{
			return 0.0;
		}

		return a_ / b_;
	}

	template <Numeric T>
	static inline constexpr T Abs(T value) noexcept
	{
		if (value < 0.0)
		{
			return value * -1.0;
		}

		return value;
	}

	template <FloatLike T>
	static inline constexpr T Dot2D(T aa_, T ab_, T ba_, T bb_){ return (aa_ * ba_) + (ab_ * bb_); }

	template <FloatLike T>
	static inline constexpr T Dot3D(T aa_, T ab_, T ac_, T ba_, T bb_, T bc_){ return (aa_ * ba_) + (ab_ * bb_) + (ac_ * bc_); }

	template <FloatLike T>
	static inline constexpr T Dot4D(T aa_, T ab_, T ac_, T ad_, T ba_, T bb_, T bc_, T bd_){ return (aa_ * ba_) + (ab_ * bb_) + (ac_ * bc_) + (ad_ * bd_); }

	template <Numeric T>
	static inline constexpr T Clamp(T min, T max, T value) noexcept
	{
		if (value < min)
		{
			return min;
		}
		else if (value > max)
		{
			return max;
		}

		return value;
	}

	static inline bool IsPrime(uint64_t num)
	{
		if (num <= 1)
		{
			return false;
		}

		if (num == 2)
		{
			return true;
		}

		if (num % 2 == 0)
		{
			return false;
		}

		auto sqrtNum = Sqrt<uint64_t>(num); // TODO - constexpr in C++26
		for (uint64_t i = 3; i <= sqrtNum; i += 2)
		{
			if (num % i == 0)
			{
				return false;
			}
		}

		return true;
	}

	static inline uint64_t NextPrime(uint64_t start){
		if (start >= LargestPrime)
		{
			return 0;
		}

		for (uint64_t i = start + 1; i <= std::numeric_limits<uint64_t>::max(); i++)
		{
			if (IsPrime(i))
			{
				return i;
			}
		}

		return 0;
	}
}