#pragma once

#include <span>

#include "CoreMath.hpp"
#include "Euler.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Rect.hpp"
#include "Vector.hpp"

namespace Gadget::Math
{
	template <FloatLike T>
	[[nodiscard]] inline constexpr TEuler<T> ToEuler(const TQuat<T>& quat) noexcept
	{
		T heading = 0.0;
		T attitude = 0.0;
		T bank = 0.0;

		const auto sqw = quat.w * quat.w;
		const auto sqx = quat.x * quat.x;
		const auto sqy = quat.y * quat.y;
		const auto sqz = quat.z * quat.z;
		const auto unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
		const auto test = (quat.x * quat.y) + (quat.z * quat.w);

		if (test > 0.499 * unit)
		{
			// singularity at north pole
			heading = 2.0 * Math::Atan2R(quat.x, quat.w);
			attitude = Math::TPi<T> / 2.0;
			bank = 0.0f;
		}
		else if (test < -0.499 * unit)
		{
			// singularity at south pole
			heading = -2.0 * Math::Atan2R(quat.x, quat.w);
			attitude = -Math::TPi<T> / 2.0;
			bank = 0.0;
		}
		else
		{
			heading = Math::Atan2R(2.0 * quat.y * quat.w - 2.0 * quat.x * quat.z, sqx - sqy - sqz + sqw);
			attitude = Math::AsinR(2.0 * test / unit);
			bank = Math::Atan2R(2.0 * quat.x * quat.w - 2.0 * quat.y * quat.z, -sqx + sqy - sqz + sqw);
		}
		
		return TEuler<T>(Math::RadiansToDegrees(bank), Math::RadiansToDegrees(heading), Math::RadiansToDegrees(attitude));
	}

	template <FloatLike T>
	[[nodiscard]] inline constexpr TQuat<T> ToQuaternion(const TEuler<T>& euler) noexcept
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
	[[nodiscard]] inline constexpr TMat3<T> ToMatrix3(const TMat4<T>& inMat)
	{
		auto mat = TMat3<T>::Identity();
		mat[0] = inMat[0];	mat[1] = inMat[1];	mat[2] = inMat[2];
		mat[3] = inMat[4];	mat[4] = inMat[5];	mat[5] = inMat[6];
		mat[6] = inMat[8];	mat[7] = inMat[9];	mat[8] = inMat[10];
		return mat;
	}

	template <FloatLike T>
	[[nodiscard]] inline constexpr TMat4<T> ToMatrix4(const TMat3<T>& inMat)
	{
		auto mat = TMat4<T>::Identity();
		mat[0] = inMat[0];	mat[4] = inMat[3];	mat[8] = inMat[6];
		mat[1] = inMat[1];	mat[5] = inMat[4];	mat[9] = inMat[7];
		mat[2] = inMat[2];	mat[6] = inMat[5];	mat[10] = inMat[8];
		return mat;
	}

	template <FloatLike T>
	[[nodiscard]] inline constexpr TMat4<T> ToMatrix4(const TQuat<T>& quat)
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
	[[nodiscard]] inline constexpr TVec4<T> ToVector4(const TVec3<T>& vec, T w = 1.0)
	{
		return TVec4<T>(vec.x, vec.y, vec.z, w);
	}

	template <FloatLike T>
	[[nodiscard]] inline constexpr TMat4<T> Translate(const TVec3<T>& v)
	{
		return TMat4<T>(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			v.x, v.y, v.z, 1.0
		);
	}

	template <FloatLike T>
	[[nodiscard]] inline constexpr TMat4<T> Rotate(T angle, const TVec3<T>& vec)
	{
		const TVec3<T> rotAxis = vec.Normal();
		const auto radAngle = Math::DegreesToRadians(angle);
		const auto cosAngle = Math::CosR(radAngle);
		const auto sinAngle = Math::SinR(radAngle);
		const auto cosM = (1.0 - cosAngle);

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
	[[nodiscard]] inline constexpr TMat4<T> Scale(const TVec3<T>& v)
	{
		return TMat4<T>(
			v.x, 0.0, 0.0, 0.0,
			0.0, v.y, 0.0, 0.0,
			0.0, 0.0, v.z, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}

	template <FloatLike T>
	[[nodiscard]] inline constexpr TRect<T> CalculateBounds(std::span<TVec2<T>> verts)
	{
		TRect<T> result;
		for (const auto& v : verts)
		{
			result.AddBounds(v);
		}

		return result;
	}
}
