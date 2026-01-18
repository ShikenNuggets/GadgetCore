#pragma once

#include <cmath>

#include "GCore/Math/CoreMath.hpp"
#include "GCore/Math/Vector.hpp"

namespace Gadget
{
	struct Color
	{
		float r, g, b, a;

		constexpr Color(float r_, float g_, float b_, float a_ = 1.0) noexcept :
			r(Math::Clamp(0.0f, 1.0f, r_)),
			g(Math::Clamp(0.0f, 1.0f, g_)),
			b(Math::Clamp(0.0f, 1.0f, b_)),
			a(Math::Clamp(0.0f, 1.0f, a_))
		{}

		[[nodiscard]] inline constexpr Color operator+(const Color& c) const noexcept{ return Color(r + c.r, g + c.g, b + c.b, a + c.a); }
		[[nodiscard]] inline constexpr Color operator*(const Vector4& v) const noexcept{ return Color(r * v.x, g * v.y, b * v.z, a * v.w); }

		inline constexpr void operator+=(const Color& c) noexcept{ *this = *this + c; }
		inline constexpr void operator*=(const Vector4& v) noexcept{ *this = *this * v; }

		static inline constexpr float ToSRGBValue(float linearValue)
		{
			if(linearValue < 0.00313066844250063f)
			{
				return linearValue * 12.92f;
			}

			return 1.055f * (std::pow(linearValue, 1.0f / 2.4f)) - 0.055f;
		}

		static inline constexpr float ToLinearValue(float srgbValue)
		{
			if(srgbValue < 0.0404482362771082f)
			{
				return srgbValue / 12.92f;
			}

			return std::pow(((srgbValue + 0.055f) / 1.055f), 2.4);
		}

		inline constexpr Color ToSRGB() const
		{
			return Color(ToSRGBValue(r), ToSRGBValue(g), ToSRGBValue(b), a);
		}

		inline constexpr Color ToLinear() const
		{
			return Color(ToLinearValue(r), ToLinearValue(g), ToLinearValue(b), a);
		}
	};
}
