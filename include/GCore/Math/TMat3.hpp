#pragma once

#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	// Column Major Order
	// [0][3][6]
	// [1][4][7]
	// [2][5][8]
	template <Math::FloatLike T>
	class TMat3
	{
	public:
		static inline constexpr size_t RowSize() noexcept{ return 3; }
		static inline constexpr size_t Size() noexcept{ return RowSize() * RowSize(); }

		constexpr TMat3() : m{ 1.0, 0.0, 0.0, /**/ 0.0, 1.0, 0.0, /**/ 0.0, 0.0, 1.0}{}

		constexpr TMat3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3) : m{}
		{
			m[0] = a1;
			m[1] = a2;
			m[2] = a3;

			m[3] = b1;
			m[4] = b2;
			m[5] = b3;

			m[6] = c1;
			m[7] = c2;
			m[8] = c3;
		}

		inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

		inline constexpr T& operator[](size_t i)
		{
			return m.at(i);
		}

		static inline constexpr TMat3 Identity()
		{
			return TMat3(1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,
				0.0, 0.0, 1.0
			);
		}

		inline constexpr T Determinant() const noexcept
		{
			return m[0] * (m[4] * m[8] - m[7] * m[5]) -
				m[1] * (m[3] * m[8] - m[5] * m[6]) +
				m[2] * (m[3] * m[7] - m[4] * m[6]);
		}

		inline constexpr TMat3 Inverse() const noexcept
		{
			const auto invDet = Math::SafeDivide(1.0, Determinant());
			return TMat3(
				(m[4] * m[8] - m[7] * m[5]) * invDet,
				(m[2] * m[7] - m[1] * m[8]) * invDet,
				(m[1] * m[5] - m[2] * m[4]) * invDet,
				(m[5] * m[6] - m[3] * m[8]) * invDet,
				(m[0] * m[8] - m[2] * m[6]) * invDet,
				(m[3] * m[2] - m[0] * m[5]) * invDet,
				(m[3] * m[7] - m[6] * m[4]) * invDet,
				(m[6] * m[1] - m[0] * m[7]) * invDet,
				(m[0] * m[4] - m[3] * m[1]) * invDet
			);
		}

	private:
		std::array<T, Size()> m;
	};
}
