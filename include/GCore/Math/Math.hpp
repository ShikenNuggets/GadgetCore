#pragma once

#include "CoreMath.hpp"
#include "Euler.hpp"
#include "Matrix.hpp"
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

	template <FloatLike T>
	inline constexpr TMat4<T> ToMatrix4(const TQuat<T>& quat)
	{
		const auto q = quat.Normal();
		const auto x2 = q.x * q.x;
		const auto y2 = q.y * q.y;
		const auto z2 = q.z * q.z;

		auto mat = TMat4<T>::Identity();
		mat[0] = 1.0 - (2.0 * y2) - (2.0 * z2);
		mat[4] = (2.0 * q.x * q.y) - (2.0 * q.z * q.w);
		mat[8] = (2.0 * q.x * q.z) + (2.0 * q.y * q.w);

		mat[1] = (2.0 * q.x * q.y) + (2.0 * q.z * q.w);
		mat[5] = 1.0 - (2.0 * x2) - (2.0 * z2);
		mat[9] = 2.0 * q.y * q.z - 2.0 * q.x * q.w;

		mat[2] = (2.0 * q.x * q.z) - (2.0 * q.y * q.w);
		mat[6] = (2.0 * q.y * q.z) + (2.0 * q.x * q.w);
		mat[10] = 1.0 - (2.0 * x2) - (2.0 * y2);
		return mat;
	}

	template <FloatLike T>
	inline constexpr TMat4<T> Translate(const TVec3<T>& v)
	{
		return TMat4<T>(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			v.x, v.y, v.z, 1.0
		);
	}

	template <FloatLike T>
	inline constexpr TMat4<T> Rotate(T angle, const TVec3<T>& vec)
	{
		TVec3<T> rotAxis = vec.Normal();
		const float radAngle = Math::DegreesToRadians(angle);
		const float cosAngle = Math::CosR(radAngle);
		const float sinAngle = Math::SinR(radAngle);
		const float cosM = (1.0 - cosAngle);

		TMat4<T> m;
		m[0] = (rotAxis.x * rotAxis.x * cosM) + cosAngle;
		m[1] = (rotAxis.x * rotAxis.y * cosM) + (rotAxis.z * sinAngle);
		m[2] = (rotAxis.x * rotAxis.z * cosM) - (rotAxis.y * sinAngle);
		m[3] = 0.0;
		m[4] = (rotAxis.x * rotAxis.y * cosM) - (rotAxis.z * sinAngle);
		m[5] = (rotAxis.y * rotAxis.y * cosM) + cosAngle;
		m[6] = (rotAxis.y * rotAxis.z * cosM) + (rotAxis.x * sinAngle);
		m[7] = 0.0;
		m[8] = (rotAxis.x * rotAxis.z * cosM) + (rotAxis.y * sinAngle);
		m[9] = (rotAxis.y * rotAxis.z * cosM) - (rotAxis.x * sinAngle);
		m[10] = (rotAxis.z * rotAxis.z * cosM) + cosAngle;
		m[11] = 0.0;
		m[12] = 0.0;
		m[13] = 0.0;
		m[14] = 0.0;
		m[15] = 1.0;
		return m;
	}

	template <FloatLike T>
	inline constexpr TMat4<T> Scale(const TVec3<T>& v)
	{
		return TMat4<T>(
			v.x, 0.0, 0.0, 0.0,
			0.0, v.y, 0.0, 0.0,
			0.0, 0.0, v.z, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}
}
