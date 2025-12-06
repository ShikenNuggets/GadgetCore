#pragma once

#include "CoreMath.hpp"
#include "Euler.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"

namespace Gadget::Math
{
	template <FloatLike T>
	inline constexpr TQuat<T> ToQuaternion(const TEuler<T>& euler) noexcept
	{
		const auto bank = DegreesToRadians(euler.x);
		const auto heading = DegreesToRadians(euler.y);
		const auto attitude = DegreesToRadians(euler.z);

		const auto c1 = Math::CosR(heading / 2.0f);
		const auto c2 = Math::CosR(attitude / 2.0f);
		const auto c3 = Math::CosR(bank / 2.0f);

		const auto s1 = Math::SinR(heading / 2.0f);
		const auto s2 = Math::SinR(attitude / 2.0f);
		const auto s3 = Math::SinR(bank / 2.0f);

		const auto newW = (c1 * c2 * c3) - (s1 * s2 * s3);
		const auto newX = (s1 * s2 * c3) + (c1 * c2 * s3);
		const auto newY = (s1 * c2 * c3) + (c1 * s2 * s3);
		const auto newZ = (c1 * s2 * c3) - (s1 * c2 * s3);

		return TQuat(newW, newX, newY, newZ).Normal();
	}
}
