#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	// Column Major Order
	// [0][2]
	// [1][3]
	template <Math::FloatLike T>
	class TMat2
	{
	public:
		static inline constexpr size_t RowSize() noexcept{ return 2; }
		static inline constexpr size_t Size() noexcept{ return RowSize() * RowSize(); }

		constexpr TMat2() : m{ 1.0, 0.0, 0.0, 1.0 }{}

		constexpr TMat2(T a1, T a2, T b1, T b2) : m{}
		{
			m[0] = a1;
			m[1] = a2;

			m[2] = b1;
			m[3] = b2;
		}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

		inline constexpr T& operator[](size_t i)
		{
			return m.at(i);
		}

		static inline constexpr TMat2 Identity()
		{
			return TMat2(1.0, 0.0,
				0.0, 1.0
			);
		}

		inline constexpr T Determinant() const noexcept
		{
			return (m[0] * m[3]) - (m[2] * m[1]);
		}

		inline constexpr TMat2 Inverse() const noexcept
		{
			const auto invDet = Math::SafeDivide(1.0, Determinant());
			return TMat2(
				m[3] * invDet, -m[1] * invDet,
				-m[2] * invDet, m[0] * invDet
			);
		}

		inline constexpr bool IsValid() const
		{
			for (const auto& v : m)
			{
				if (!Math::IsValidNumber(v))
				{
					return false;
				}
			}

			return true;
		}

	private:
		std::array<T, Size()> m;
	};
}
