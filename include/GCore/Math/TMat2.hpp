#pragma once

#include <algorithm>
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

		[[nodiscard]] inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

		[[nodiscard]] inline constexpr T& operator[](size_t i)
		{
			return m.at(i);
		}

		[[nodiscard]] inline constexpr TMat2 operator*(const TMat2& m_) const
		{
			return TMat2(
				//COLUMN 1
				Math::Dot2D(/*A*/ m[0], m[2], /*B*/ m_[0], m_[1]),
				Math::Dot2D(/*A*/ m[1], m[3], /*B*/ m_[0], m_[1]),
				//COLUMN 2
				Math::Dot2D(/*A*/ m[0], m[2], /*B*/ m_[2], m_[3]),
				Math::Dot2D(/*A*/ m[1], m[3], /*B*/ m_[2], m_[3])
			);
		}

		inline constexpr void operator*=(const TMat2& m_){ *this = *this * m_; }

		[[nodiscard]] static inline constexpr TMat2 Identity()
		{
			return TMat2(1.0, 0.0,
				0.0, 1.0
			);
		}

		[[nodiscard]] inline constexpr TMat2 Transpose() const
		{
			return TMat2(
				m[0], m[2],
				m[1], m[3]
			);
		}

		[[nodiscard]] inline constexpr T Determinant() const noexcept
		{
			return (m[0] * m[3]) - (m[2] * m[1]);
		}

		[[nodiscard]] inline constexpr TMat2 Inverse() const noexcept
		{
			const auto invDet = Math::SafeDivide(1.0, Determinant());
			return TMat2(
				m[3] * invDet, -m[1] * invDet,
				-m[2] * invDet, m[0] * invDet
			);
		}

		[[nodiscard]] inline constexpr bool IsValid() const
		{
			return std::ranges::all_of(m, [](const auto& v){ return Math::IsValidNumber(v); });
		}

	private:
		std::array<T, Size()> m;
	};
}
