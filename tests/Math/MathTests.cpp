#include <catch2/catch_all.hpp>

#include "GCore/Math/Math.hpp"

using namespace Gadget;
using Catch::Approx;

TEST_CASE("Math::ToEuler(Quaternion)", "[math_to_euler_quaternion]")
{
	auto q = Quaternion::Identity();
	auto e = Math::ToEuler(q);
	REQUIRE(e.x == 0.0);
	REQUIRE(e.y == 0.0);
	REQUIRE(e.z == 0.0);

	q = Quaternion(Math::CosR(Math::Pi / 4.0), 0.0, Math::SinR(Math::Pi / 4.0), 0.0);
	e = Math::ToEuler(q);
	REQUIRE(e.x == Approx(0.0));
	REQUIRE(e.y == Approx(90.0));
	REQUIRE(e.z == Approx(0.0));

	q = Quaternion(Math::CosR(Math::Pi / 4.0), Math::SinR(Math::Pi / 4.0), 0.0, 0.0);
	e = Math::ToEuler(q);
	REQUIRE(e.x == Approx(90.0));
	REQUIRE(e.y == Approx(0.0));
	REQUIRE(e.z == Approx(0.0));

	q = Quaternion(Math::CosR(Math::Pi / 4.0), 0.0, 0.0, Math::SinR(Math::Pi / 4.0));
	e = Math::ToEuler(q);
	REQUIRE(e.x == Approx(0.0));
	REQUIRE(e.y == Approx(0.0));
	REQUIRE(e.z == Approx(90.0));
}

TEST_CASE("Math::ToQuaternion(Euler)", "[math_to_quaternion_euler]")
{
	auto e = Euler();
	auto q = Math::ToQuaternion(e);
	REQUIRE(q.Magnitude() == Approx(1.0));
	REQUIRE(q.w == Approx(1.0));
	REQUIRE(q.x == Approx(0.0));
	REQUIRE(q.y == Approx(0.0));
	REQUIRE(q.z == Approx(0.0));

	e = Euler(0.0, 90.0, 0.0);
	q = Math::ToQuaternion(e);
	REQUIRE(q.Magnitude() == Approx(1.0));
	REQUIRE(q.w == Approx(Math::CosR(Math::Pi / 4.0)));
	REQUIRE(q.x == Approx(0.0));
	REQUIRE(q.y == Approx(Math::SinR(Math::Pi / 4.0)));
	REQUIRE(q.z == Approx(0.0));

	e = Euler(90.0, 0.0, 0.0);
	q = Math::ToQuaternion(e);
	REQUIRE(q.Magnitude() == Approx(1.0));
	REQUIRE(q.w == Approx(Math::CosR(Math::Pi / 4.0)));
	REQUIRE(q.x == Approx(Math::SinR(Math::Pi / 4.0)));
	REQUIRE(q.y == Approx(0.0));
	REQUIRE(q.z == Approx(0.0));

	e = Euler(0.0, 0.0, 90.0);
	q = Math::ToQuaternion(e);
	REQUIRE(q.Magnitude() == Approx(1.0));
	REQUIRE(q.w == Approx(Math::CosR(Math::Pi / 4.0)));
	REQUIRE(q.x == Approx(0.0));
	REQUIRE(q.y == Approx(0.0));
	REQUIRE(q.z == Approx(Math::SinR(Math::Pi / 4.0)));

	e = Euler(45.0, 45.0, 45.0);
	q = Math::ToQuaternion(e);
	REQUIRE(q.Magnitude() == Approx(1.0));
}

TEST_CASE("Math::ToMatrix3(TMat4)", "[math_to_matrix3_tmat4]")
{
	const auto mat4 = Matrix4(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0);
	const auto mat3 = Math::ToMatrix3(mat4);
	REQUIRE(mat3[0] == mat4[0]);
	REQUIRE(mat3[1] == mat4[1]);
	REQUIRE(mat3[2] == mat4[2]);
	REQUIRE(mat3[3] == mat4[4]);
	REQUIRE(mat3[4] == mat4[5]);
	REQUIRE(mat3[5] == mat4[6]);
	REQUIRE(mat3[6] == mat4[8]);
	REQUIRE(mat3[7] == mat4[9]);
	REQUIRE(mat3[8] == mat4[10]);
}

TEST_CASE("Math::ToMatrix4(TMat3)", "[math_to_matrix4_tmat3]")
{
	const auto mat3 = Matrix3(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
	const auto mat4 = Math::ToMatrix4(mat3);
	REQUIRE(mat4[0] == mat3[0]);
	REQUIRE(mat4[1] == mat3[1]);
	REQUIRE(mat4[2] == mat3[2]);
	REQUIRE(mat4[3] == 0.0);
	REQUIRE(mat4[4] == mat3[3]);
	REQUIRE(mat4[5] == mat3[4]);
	REQUIRE(mat4[6] == mat3[5]);
	REQUIRE(mat4[7] == 0.0);
	REQUIRE(mat4[8] == mat3[6]);
	REQUIRE(mat4[9] == mat3[7]);
	REQUIRE(mat4[10] == mat3[8]);
	REQUIRE(mat4[11] == 0.0);
	REQUIRE(mat4[12] == 0.0);
	REQUIRE(mat4[13] == 0.0);
	REQUIRE(mat4[14] == 0.0);
	REQUIRE(mat4[15] == 1.0);
}

TEST_CASE("Math::ToMatrix4(TQuat)", "[math_to_matrix4_quat]")
{
	const auto qIdentity = Quaternion::Identity();
	const auto mIdentity = Matrix4::Identity();
	auto m = Math::ToMatrix4(qIdentity);
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(m[i] == mIdentity[i]);
	}

	const auto q90X = Quaternion(Math::CosR(Math::Pi / 4.0), Math::SinR(Math::Pi / 4.0), 0.0, 0.0);
	const auto m90X = Math::Rotate(90.0, Vector3(1.0, 0.0, 0.0));
	m = Math::ToMatrix4(q90X);
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(m[i] == Approx(m90X[i]).margin(1e-6));
	}

	const auto q90Y = Quaternion(Math::CosR(Math::Pi / 4.0), 0.0, Math::SinR(Math::Pi / 4.0), 0.0);
	const auto m90Y = Math::Rotate(90.0, Vector3(0.0, 1.0, 0.0));
	m = Math::ToMatrix4(q90Y);
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(m[i] == Approx(m90Y[i]).margin(1e-6));
	}

	const auto q90Z = Quaternion(Math::CosR(Math::Pi / 4.0), 0.0, 0.0, Math::SinR(Math::Pi / 4.0));
	const auto m90Z = Math::Rotate(90.0, Vector3(0.0, 0.0, 1.0));
	m = Math::ToMatrix4(q90Z);
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(m[i] == Approx(m90Z[i]).margin(1e-6));
	}

	const auto qNormal = Quaternion(Math::CosR(Math::Pi / 3.0), Math::SinR(Math::Pi / 3.0), 0.0, 0.0).Normal();
	const auto qScaled = qNormal * 3.0;
	const auto mNormal = Math::ToMatrix4(qNormal);
	const auto mScaled = Math::ToMatrix4(qScaled);
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		CHECK(mNormal[i] == Approx(mScaled[i]));
	}
}

TEST_CASE("Math::ToVector4(TVec3)", "[math_to_vector4_tvec3]")
{
	const auto vec = Vector3(1.0, 2.0, 3.0);
	auto result = Gadget::Math::ToVector4(vec);
	REQUIRE(result.x == vec.x);
	REQUIRE(result.y == vec.y);
	REQUIRE(result.z == vec.z);
	REQUIRE(result.w == 1.0);

	result = Gadget::Math::ToVector4(vec, 4.0);
	REQUIRE(result.x == vec.x);
	REQUIRE(result.y == vec.y);
	REQUIRE(result.z == vec.z);
	REQUIRE(result.w == 4.0);
}

TEST_CASE("Math::Translate", "[math_translate]")
{
	const auto identity = Matrix4::Identity();
	const auto m = Math::Translate(Vector3(1.0, 2.0, 3.0));
	REQUIRE(m[0] == identity[0]);
	REQUIRE(m[1] == identity[1]);
	REQUIRE(m[2] == identity[2]);
	REQUIRE(m[3] == identity[3]);
	REQUIRE(m[4] == identity[4]);
	REQUIRE(m[5] == identity[5]);
	REQUIRE(m[6] == identity[6]);
	REQUIRE(m[7] == identity[7]);
	REQUIRE(m[8] == identity[8]);
	REQUIRE(m[9] == identity[9]);
	REQUIRE(m[10] == identity[10]);
	REQUIRE(m[11] == identity[11]);
	REQUIRE(m[12] == 1.0);
	REQUIRE(m[13] == 2.0);
	REQUIRE(m[14] == 3.0);
	REQUIRE(m[15] == identity[15]);
}

TEST_CASE("Math::Rotate", "[math_rotate]")
{
	const auto identity = Matrix4::Identity();
	const auto noRotate = Math::Rotate(0.0, Vector3(1.0, 0.0, 0.0));
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(noRotate[i] == identity[i]);
	}

	const auto rotate90X = Math::Rotate(90.0, Vector3(1.0, 0.0, 0.0));
	REQUIRE(rotate90X[0] == Approx(identity[0]));
	REQUIRE(rotate90X[1] == identity[1]);
	REQUIRE(rotate90X[2] == identity[2]);
	REQUIRE(rotate90X[3] == identity[3]);
	REQUIRE(rotate90X[4] == identity[4]);
	REQUIRE(rotate90X[5] == Approx(0.0).margin(1e-6));
	REQUIRE(rotate90X[6] == Approx(1.0));
	REQUIRE(rotate90X[7] == identity[7]);
	REQUIRE(rotate90X[8] == identity[8]);
	REQUIRE(rotate90X[9] == Approx(-1.0));
	REQUIRE(rotate90X[10] == Approx(0.0).margin(1e-6));
	REQUIRE(rotate90X[11] == identity[11]);
	REQUIRE(rotate90X[12] == identity[12]);
	REQUIRE(rotate90X[13] == identity[13]);
	REQUIRE(rotate90X[14] == identity[14]);
	REQUIRE(rotate90X[15] == identity[15]);

	const auto rotate90Y = Math::Rotate(90.0, Vector3(0.0, 1.0, 0.0));
	REQUIRE(rotate90Y[0] == Approx(0.0).margin(1e-6));
	REQUIRE(rotate90Y[1] == identity[1]);
	REQUIRE(rotate90Y[2] == Approx(-1.0));
	REQUIRE(rotate90Y[3] == identity[3]);
	REQUIRE(rotate90Y[4] == identity[4]);
	REQUIRE(rotate90Y[5] == Approx(identity[5]));
	REQUIRE(rotate90Y[6] == Approx(identity[6]));
	REQUIRE(rotate90Y[7] == identity[7]);
	REQUIRE(rotate90Y[8] == Approx(1.0));
	REQUIRE(rotate90Y[9] == Approx(identity[9]));
	REQUIRE(rotate90Y[10] == Approx(0.0).margin(1e-6));
	REQUIRE(rotate90Y[11] == identity[11]);
	REQUIRE(rotate90Y[12] == identity[12]);
	REQUIRE(rotate90Y[13] == identity[13]);
	REQUIRE(rotate90Y[14] == identity[14]);
	REQUIRE(rotate90Y[15] == identity[15]);

	const auto rotate90Z = Math::Rotate(90.0, Vector3(0.0, 0.0, 1.0));
	REQUIRE(rotate90Z[0] == Approx(0.0).margin(1e-6));
	REQUIRE(rotate90Z[1] == Approx(1.0));
	REQUIRE(rotate90Z[2] == identity[2]);
	REQUIRE(rotate90Z[3] == identity[3]);
	REQUIRE(rotate90Z[4] == Approx(-1.0));
	REQUIRE(rotate90Z[5] == Approx(0.0).margin(1e-6));
	REQUIRE(rotate90Z[6] == identity[6]);
	REQUIRE(rotate90Z[7] == identity[7]);
	REQUIRE(rotate90Z[8] == identity[8]);
	REQUIRE(rotate90Z[9] == identity[9]);
	REQUIRE(rotate90Z[10] == Approx(identity[10]));
	REQUIRE(rotate90Z[11] == identity[11]);
	REQUIRE(rotate90Z[12] == identity[12]);
	REQUIRE(rotate90Z[13] == identity[13]);
	REQUIRE(rotate90Z[14] == identity[14]);
	REQUIRE(rotate90Z[15] == identity[15]);

	const auto m1 = Math::Rotate(45.0, Vector3(2, 0, 0));
	const auto m2 = Math::Rotate(45.0, Vector3(1, 0, 0));
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(m1[i] == Approx(m2[i]));
	}
}

TEST_CASE("Math::Scale", "[math_scale]")
{
	const auto identity = Matrix4::Identity();
	const auto m = Math::Scale(Vector3(1.0, 2.0, 3.0));
	REQUIRE(m[0] == 1.0);
	REQUIRE(m[1] == identity[1]);
	REQUIRE(m[2] == identity[2]);
	REQUIRE(m[3] == identity[3]);
	REQUIRE(m[4] == identity[4]);
	REQUIRE(m[5] == 2.0);
	REQUIRE(m[6] == identity[6]);
	REQUIRE(m[7] == identity[7]);
	REQUIRE(m[8] == identity[8]);
	REQUIRE(m[9] == identity[9]);
	REQUIRE(m[10] == 3.0);
	REQUIRE(m[11] == identity[11]);
	REQUIRE(m[12] == identity[12]);
	REQUIRE(m[13] == identity[13]);
	REQUIRE(m[14] == identity[14]);
	REQUIRE(m[15] == identity[15]);
}

TEST_CASE("Math::CalculateBounds", "[math_calculate_bounds]")
{
	std::vector<Vector2> vecs;
	vecs.emplace_back(1.0, 2.0);
	vecs.emplace_back(3.0, 4.0);
	vecs.emplace_back(5.0, 6.0);

	const auto bounds = Math::CalculateBounds<Math::GFloat>(vecs);
	REQUIRE(bounds.min.x == 1.0);
	REQUIRE(bounds.min.y == 2.0);
	REQUIRE(bounds.max.x == 5.0);
	REQUIRE(bounds.max.y == 6.0);
}
