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

		void AddBounds(T x, T y)
		{
			min.x = std::min(min.x, x);
			min.y = std::min(min.y, y);
			max.x = std::max(max.x, x);
			max.y = std::max(max.y, y);
		}

		void AddBounds(const TVec2<T>& v)
		{
			AddBounds(v.x, v.y);
		}
	};

	using Rect = TRect<Math::GFloat>;
}
