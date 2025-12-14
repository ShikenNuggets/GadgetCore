#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

#include "CoreMath.hpp"

namespace Gadget
{
	// Column Major Order
	// [00][04][08][12]
	// [01][05][09][13]
	// [02][06][10][14]
	// [03][07][11][15]
	template <Math::FloatLike T>
	class TMat4
	{
	public:
		static inline constexpr size_t RowSize() noexcept{ return 4; }
		static inline constexpr size_t Size() noexcept{ return RowSize() * RowSize(); }

		constexpr TMat4() : m{ 1.0, 0.0, 0.0, 0.0, /**/ 0.0, 1.0, 0.0, 0.0, /**/ 0.0, 0.0, 1.0, 0.0, /**/ 0.0, 0.0, 0.0, 1.0 }{}
		
		constexpr TMat4(T a1, T a2, T a3, T a4, T b1, T b2, T b3, T b4, T c1, T c2, T c3, T c4, T d1, T d2, T d3, T d4) : m{}
		{
			m[0] = a1;
			m[1] = a2;
			m[2] = a3;
			m[3] = a4;

			m[4] = b1;
			m[5] = b2;
			m[6] = b3;
			m[7] = b4;

			m[8] = c1;
			m[9] = c2;
			m[10] = c3;
			m[11] = c4;

			m[12] = d1;
			m[13] = d2;
			m[14] = d3;
			m[15] = d4;
		}

		[[nodiscard]] inline constexpr T operator [](size_t i) const
		{
			return m.at(i);
		}

		[[nodiscard]] inline constexpr T& operator[](size_t i)
		{
			return m.at(i);
		}

		[[nodiscard]] TMat4 operator*(const TMat4& m_) const
		{
			return TMat4(
				//COLUMN 1
				Math::Dot4D(/*A*/ m[0], m[4], m[8], m[12], /*B*/ m_[0], m_[1], m_[2], m_[3]),
				Math::Dot4D(/*A*/ m[1], m[5], m[9], m[13], /*B*/ m_[0], m_[1], m_[2], m_[3]),
				Math::Dot4D(/*A*/ m[2], m[6], m[10], m[14], /*B*/ m_[0], m_[1], m_[2], m_[3]),
				Math::Dot4D(/*A*/ m[3], m[7], m[11], m[15], /*B*/ m_[0], m_[1], m_[2], m_[3]),
				//COLUMN 2
				Math::Dot4D(/*A*/ m[0], m[4], m[8], m[12], /*B*/ m_[4], m_[5], m_[6], m_[7]),
				Math::Dot4D(/*A*/ m[1], m[5], m[9], m[13], /*B*/ m_[4], m_[5], m_[6], m_[7]),
				Math::Dot4D(/*A*/ m[2], m[6], m[10], m[14], /*B*/ m_[4], m_[5], m_[6], m_[7]),
				Math::Dot4D(/*A*/ m[3], m[7], m[11], m[15], /*B*/ m_[4], m_[5], m_[6], m_[7]),
				//COLUMN 3
				Math::Dot4D(/*A*/ m[0], m[4], m[8], m[12], /*B*/ m_[8], m_[9], m_[10], m_[11]),
				Math::Dot4D(/*A*/ m[1], m[5], m[9], m[13], /*B*/ m_[8], m_[9], m_[10], m_[11]),
				Math::Dot4D(/*A*/ m[2], m[6], m[10], m[14], /*B*/ m_[8], m_[9], m_[10], m_[11]),
				Math::Dot4D(/*A*/ m[3], m[7], m[11], m[15], /*B*/ m_[8], m_[9], m_[10], m_[11]),
				//COLUMN 4
				Math::Dot4D(/*A*/ m[0], m[4], m[8], m[12], /*B*/ m_[12], m_[13], m_[14], m_[15]),
				Math::Dot4D(/*A*/ m[1], m[5], m[9], m[13], /*B*/ m_[12], m_[13], m_[14], m_[15]),
				Math::Dot4D(/*A*/ m[2], m[6], m[10], m[14], /*B*/ m_[12], m_[13], m_[14], m_[15]),
				Math::Dot4D(/*A*/ m[3], m[7], m[11], m[15], /*B*/ m_[12], m_[13], m_[14], m_[15])
			);
		}

		inline constexpr void operator*=(const TMat4& m_){ *this = *this * m_; }

		[[nodiscard]] static inline constexpr TMat4 Identity()
		{
			return TMat4(1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0
			);
		}

		[[nodiscard]] inline constexpr TMat4 Transpose() const
		{
			return TMat4(
				m[0], m[4], m[8], m[12],
				m[1], m[5], m[9], m[13],
				m[2], m[6], m[10], m[14],
				m[3], m[7], m[11], m[15]
			);
		}

		[[nodiscard]] inline constexpr T Determinant() const noexcept
		{
			return
				m[0] * (m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10])
				- m[4] * (m[1] * m[10] * m[15] - m[1] * m[11] * m[14] - m[9] * m[2] * m[15] + m[9] * m[3] * m[14] + m[13] * m[2] * m[11] - m[13] * m[3] * m[10])
				+ m[8] * (m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6])
				- m[12] * (m[1] * m[6] * m[11] - m[1] * m[10] * m[7] - m[5] * m[2] * m[11] + m[5] * m[8] * m[3] + m[9] * m[2] * m[7] - m[9] * m[8] * m[3]);
		}

		[[nodiscard]] inline constexpr TMat4 Inverse() const noexcept
		{
			const auto invDet = Math::SafeDivide(1.0, Determinant());
			return TMat4<T>(
				invDet * (m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10]),
				invDet * (-m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10]),
				invDet * (m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6]),
				invDet * (-m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6]),
				invDet * (-m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10]),
				invDet * (m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10]),
				invDet * (-m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6]),
				invDet * (m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6]),
				invDet * (m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9]),
				invDet * (-m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9]),
				invDet * (m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5]),
				invDet * (-m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5]),
				invDet * (-m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9]),
				invDet * (m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9]),
				invDet * (-m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5]),
				invDet * (m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5])
			);
		}

		[[nodiscard]] static inline constexpr TMat4 Orthographic(T left, T right, T bottom, T top, T nearPlane = -1.0, T farPlane = 1.0)
		{
			auto ortho = TMat4();

			ortho[0] = 2.0 / (right - left);
			ortho[5] = 2.0 / (top - bottom);
			ortho[10] = -2.0 / (farPlane - nearPlane);
			ortho[12] = -(right + left) / (right - left);
			ortho[13] = -(top + bottom) / (top - bottom);
			ortho[14] = -(farPlane + nearPlane) / (farPlane - nearPlane);
			ortho[15] = 1.0;

			return ortho;
		}

		[[nodiscard]] static inline constexpr TMat4 Perspective(T fov, T aspect, T nearPlane, T farPlane)
		{
			const auto cot = 1.0 / Math::Tan(fov * 0.5);
			return TMat4(cot / aspect, 0.0, 0.0, 0.0,
				0.0, cot, 0.0, 0.0,
				0.0, 0.0, (nearPlane + farPlane) / (nearPlane - farPlane), -1.0,
				0.0, 0.0, (2.0 * nearPlane * farPlane) / (nearPlane - farPlane), 0.0
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
