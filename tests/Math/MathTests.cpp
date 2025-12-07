#include <catch2/catch_all.hpp>

#include "GCore/Math/Math.hpp"

using namespace Gadget;
using Math::Approx;

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
		REQUIRE(m[i] == Approx(m90X[i]));
	}

	const auto q90Y = Quaternion(Math::CosR(Math::Pi / 4.0), 0.0, Math::SinR(Math::Pi / 4.0), 0.0);
	const auto m90Y = Math::Rotate(90.0, Vector3(0.0, 1.0, 0.0));
	m = Math::ToMatrix4(q90Y);
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(m[i] == Approx(m90Y[i]));
	}

	const auto q90Z = Quaternion(Math::CosR(Math::Pi / 4.0), 0.0, 0.0, Math::SinR(Math::Pi / 4.0));
	const auto m90Z = Math::Rotate(90.0, Vector3(0.0, 0.0, 1.0));
	m = Math::ToMatrix4(q90Z);
	for (size_t i = 0; i < Matrix4::Size(); ++i)
	{
		REQUIRE(m[i] == Approx(m90Z[i]));
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
	REQUIRE(rotate90X[5] == Approx(0.0));
	REQUIRE(rotate90X[6] == Approx(1.0));
	REQUIRE(rotate90X[7] == identity[7]);
	REQUIRE(rotate90X[8] == identity[8]);
	REQUIRE(rotate90X[9] == Approx(-1.0));
	REQUIRE(rotate90X[10] == Approx(0.0));
	REQUIRE(rotate90X[11] == identity[11]);
	REQUIRE(rotate90X[12] == identity[12]);
	REQUIRE(rotate90X[13] == identity[13]);
	REQUIRE(rotate90X[14] == identity[14]);
	REQUIRE(rotate90X[15] == identity[15]);

	const auto rotate90Y = Math::Rotate(90.0, Vector3(0.0, 1.0, 0.0));
	REQUIRE(rotate90Y[0] == Approx(0.0));
	REQUIRE(rotate90Y[1] == identity[1]);
	REQUIRE(rotate90Y[2] == Approx(-1.0));
	REQUIRE(rotate90Y[3] == identity[3]);
	REQUIRE(rotate90Y[4] == identity[4]);
	REQUIRE(rotate90Y[5] == Approx(identity[5]));
	REQUIRE(rotate90Y[6] == Approx(identity[6]));
	REQUIRE(rotate90Y[7] == identity[7]);
	REQUIRE(rotate90Y[8] == Approx(1.0));
	REQUIRE(rotate90Y[9] == Approx(identity[9]));
	REQUIRE(rotate90Y[10] == Approx(0.0));
	REQUIRE(rotate90Y[11] == identity[11]);
	REQUIRE(rotate90Y[12] == identity[12]);
	REQUIRE(rotate90Y[13] == identity[13]);
	REQUIRE(rotate90Y[14] == identity[14]);
	REQUIRE(rotate90Y[15] == identity[15]);

	const auto rotate90Z = Math::Rotate(90.0, Vector3(0.0, 0.0, 1.0));
	REQUIRE(rotate90Z[0] == Approx(0.0));
	REQUIRE(rotate90Z[1] == Approx(1.0));
	REQUIRE(rotate90Z[2] == identity[2]);
	REQUIRE(rotate90Z[3] == identity[3]);
	REQUIRE(rotate90Z[4] == Approx(-1.0));
	REQUIRE(rotate90Z[5] == Approx(0.0));
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
