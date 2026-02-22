#pragma once

#include <algorithm>

#include "CoreMath.hpp"
#include "TVec2.hpp"

namespace Gadget
{
	template<Math::FloatLike T>
	struct TRect
	{
		TVec2<T> min;
		TVec2<T> max;

		explicit constexpr TRect() noexcept : min(Math::TInfinity<T>, Math::TInfinity<T>), max(-Math::TInfinity<T>, -Math::TInfinity<T>){}
		explicit constexpr TRect(TVec2<T> min_, TVec2<T> max_) noexcept : min(min_), max(max_){}
		explicit constexpr TRect(T xMin, T yMin, T xMax, T yMax) noexcept : min(xMin, yMin), max(xMax, yMax){}

		inline constexpr void AddBounds(T x, T y)
		{
			min.x = std::min(min.x, x);
			min.y = std::min(min.y, y);
			max.x = std::max(max.x, x);
			max.y = std::max(max.y, y);
		}

		inline constexpr void AddBounds(const TVec2<T>& v)
		{
			AddBounds(v.x, v.y);
		}

		[[nodiscard]] inline constexpr TVec2<T> GetSize() const noexcept{ return max - min; }
		[[nodiscard]] inline constexpr T GetWidth() const noexcept{ return max.x - min.x; }
		[[nodiscard]] inline constexpr T GetHeight() const noexcept{ return max.y - min.y; }

		[[nodiscard]] inline constexpr bool Intersects(T x, T y) const noexcept
		{
			return x >= min.x && x <= max.x && y >= min.y && y <= max.y;
		}

		[[nodiscard]] inline constexpr bool Intersects(TVec2<T> point) const noexcept
		{
			return Intersects(point.x, point.y);
		}

		[[nodiscard]] inline bool IsValid() const{ return min.IsValid() && max.IsValid(); }
	};

	using Rect = TRect<Math::GFloat>;
}
