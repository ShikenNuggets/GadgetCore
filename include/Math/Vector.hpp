#pragma once

#include "Math.hpp"

namespace GCore
{
	template<Math::FloatLike T>
	struct TVec2
	{
		T x;
		T y;
		
		explicit constexpr TVec2(T x_ = 0.0, T y_ = 0.0) : x(x_), y(y_){}

		static inline constexpr TVec2 Zero(){ return TVec2(0.0, 0.0); }
		static inline constexpr TVec2 Fill(T value_){ return TVec2(value_, value_); }

		inline constexpr TVec2 operator -() const{ return TVec2(-x, -y); }
		inline constexpr TVec2 operator +(const TVec2& value_) const{ return TVec2(x + value_.x, y + value_.y); }
		inline constexpr TVec2 operator -(const TVec2& value_) const{ return TVec2(x - value_.x, y - value_.y); }
		inline constexpr TVec2 operator *(T value_) const{ return TVec2(x * value_, y * value_); }
		inline constexpr TVec2 operator /(T value_) const{ return TVec2(Math::SafeDivide(x, value_), Math::SafeDivide(y, value_)); }
	};

	using Vector2 = TVec2<Math::GFloat>;
}