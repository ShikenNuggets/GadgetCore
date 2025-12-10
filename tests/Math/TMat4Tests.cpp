#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat4.hpp"

using namespace Gadget;
using Catch::Approx;

TEST_CASE("TMat4::TMat4", "[tmat4_constructor]")
{
	const TMat4<double> defaultConstructed;
	const auto identity = TMat4<double>::Identity();

	for (size_t i = 0; i < 4 * 4; ++i)
	{
		REQUIRE(defaultConstructed[i] == identity[i]);
	}
}

TEST_CASE("TMat4::TMat4(T...)", "[tmat4_constructor_t]")
{
	const auto doubleMat4 = TMat4<double>(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0);
	for (size_t i = 0; i < 4 * 4; ++i)
	{
		REQUIRE(doubleMat4[i] == static_cast<double>(i));
	}
}

TEST_CASE("TMat4::operator[]", "[tmat4_operator_array]")
{
	auto mat = TMat4<double>::Identity();
	mat[0] = 0.0;
	mat[1] = 1.0;
	mat[2] = 2.0;
	mat[3] = 3.0;
	mat[4] = 4.0;
	mat[5] = 5.0;
	mat[6] = 6.0;
	mat[7] = 7.0;
	mat[8] = 8.0;
	mat[9] = 9.0;
	mat[10] = 10.0;
	mat[11] = 11.0;
	mat[12] = 12.0;
	mat[13] = 13.0;
	mat[14] = 14.0;
	mat[15] = 15.0;

	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(mat[i] == static_cast<double>(i));
	}

	REQUIRE_THROWS(mat[-1]);
	REQUIRE_THROWS(mat[TMat4<double>::Size()]);
}

TEST_CASE("TMat4::operator*(TMat4)", "[tmat4_operator_*_tmat4]")
{
	const auto identity = TMat4<double>::Identity();
	const auto zero = TMat4<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	const auto testMat1 = TMat4<double>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
	const auto testMat2 = TMat4<double>(16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

	const auto resultA = identity * testMat1;
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(resultA[i] == testMat1[i]);
	}

	const auto resultB = testMat1 * identity;
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(resultB[i] == testMat1[i]);
	}

	const auto resultC = zero * testMat1;
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(resultC[i] == zero[i]);
	}

	const auto resultD = testMat1 * testMat2;
	REQUIRE(resultD[0] == 386.0);
	REQUIRE(resultD[1] == 444.0);
	REQUIRE(resultD[2] == 502.0);
	REQUIRE(resultD[3] == 560.0);

	REQUIRE(resultD[4] == 274.0);
	REQUIRE(resultD[5] == 316.0);
	REQUIRE(resultD[6] == 358.0);
	REQUIRE(resultD[7] == 400.0);

	REQUIRE(resultD[8] == 162.0);
	REQUIRE(resultD[9] == 188.0);
	REQUIRE(resultD[10] == 214.0);
	REQUIRE(resultD[11] == 240.0);

	REQUIRE(resultD[12] == 50.0);
	REQUIRE(resultD[13] == 60.0);
	REQUIRE(resultD[14] == 70.0);
	REQUIRE(resultD[15] == 80.0);
}

TEST_CASE("TMat4::operator*=(TMat4)", "[tmat4_operator_*=_tmat4]")
{
	const auto identity = TMat4<double>::Identity();
	const auto zero = TMat4<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	const auto testMat1 = TMat4<double>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
	const auto testMat2 = TMat4<double>(16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);
	
	const auto truthA = identity * testMat1;
	auto resultA = identity;
	resultA *= testMat1;
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(resultA[i] == truthA[i]);
	}

	const auto truthB = testMat1 * identity;
	auto resultB = testMat1;
	resultB *= identity;
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(resultB[i] == truthB[i]);
	}

	const auto truthC = zero * testMat1;
	auto resultC = zero;
	resultC *= testMat1;
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(resultC[i] == truthC[i]);
	}

	const auto truthD = testMat1 * testMat2;
	auto resultD = testMat1;
	resultD *= testMat2;
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(resultD[i] == truthD[i]);
	}
}

TEST_CASE("TMat4::Identity", "[tmat4_identity]")
{
	const auto identity = TMat4<double>::Identity();
	REQUIRE(identity[0] == 1.0);
	REQUIRE(identity[1] == 0.0);
	REQUIRE(identity[2] == 0.0);
	REQUIRE(identity[3] == 0.0);

	REQUIRE(identity[4] == 0.0);
	REQUIRE(identity[5] == 1.0);
	REQUIRE(identity[6] == 0.0);
	REQUIRE(identity[7] == 0.0);

	REQUIRE(identity[8] == 0.0);
	REQUIRE(identity[9] == 0.0);
	REQUIRE(identity[10] == 1.0);
	REQUIRE(identity[11] == 0.0);

	REQUIRE(identity[12] == 0.0);
	REQUIRE(identity[13] == 0.0);
	REQUIRE(identity[14] == 0.0);
	REQUIRE(identity[15] == 1.0);
}

TEST_CASE("TMat4::Determinant", "[tmat4_determinant]")
{
	const auto identity = TMat4<double>::Identity();
	REQUIRE(identity.Determinant() == Approx(1.0));

	auto m = TMat4<double>(1.0, 0.0, 0.0, 0.0, 2.0, 1.0, 0.0, 0.0, 3.0, 2.0, 1.0, 0.0, 4.0, 3.0, 2.0, 1.0);
	REQUIRE(m.Determinant() == Approx(1.0));

	m = TMat4<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	REQUIRE(m.Determinant() == 0.0);

	m = identity;
	m[15] = -1.0;
	REQUIRE(m.Determinant() == Approx(-1.0));
}

TEST_CASE("TMat4::Inverse", "[tmat4_inverse]")
{
	const auto identity = TMat4<double>::Identity();
	const auto invId = identity.Inverse();
	for (size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(invId[i] == identity[i]);
	}

	auto m = TMat4<double>(1.0, 0.0, 0.0, 0.0, 2.0, 1.0, 0.0, 0.0, 3.0, 2.0, 1.0, 0.0, 4.0, 3.0, 2.0, 1.0).Inverse();
	REQUIRE(m[0] == Approx(1.0));
	REQUIRE(m[1] == Approx(0.0));
	REQUIRE(m[2] == Approx(0.0));
	REQUIRE(m[3] == Approx(0.0));
	REQUIRE(m[4] == Approx(-2.0));
	REQUIRE(m[5] == Approx(1.0));
	REQUIRE(m[6] == Approx(0.0));
	REQUIRE(m[7] == Approx(0.0));
	REQUIRE(m[8] == Approx(1.0));
	REQUIRE(m[9] == Approx(-2.0));
	REQUIRE(m[10] == Approx(1.0));
	REQUIRE(m[11] == Approx(0.0));
	REQUIRE(m[12] == Approx(0.0));
	REQUIRE(m[13] == Approx(1.0));
	REQUIRE(m[14] == Approx(-2.0));
	REQUIRE(m[15] == Approx(1.0));

	// TODO - Matrix * Inverse == Identity

	m = TMat4<double>(1.0, 2.0, 0.0, 0.0, 2.0, 4.0, 0.0, 0.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0).Inverse();
	for(size_t i = 0; i < TMat4<double>::Size(); ++i)
	{
		REQUIRE(m[i] == 0.0);
	}
}

TEST_CASE("TMat4::Orthographic", "[tmat4_orthographic]")
{
	auto m = TMat4<double>::Orthographic(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	REQUIRE(m[0] == Approx(1.0));
	REQUIRE(m[5] == Approx(1.0));
	REQUIRE(m[10] == Approx(-1.0));
	REQUIRE(m[15] == Approx(1.0));
	REQUIRE(m[12] == Approx(0.0));
	REQUIRE(m[13] == Approx(0.0));
	REQUIRE(m[14] == Approx(0.0));

	const auto left = -2.0;
	const auto right = 6.0;
	const auto bottom = -1.0;
	const auto top = 3.0;
	const auto near = -5.0;
	const auto far = 15.0;

	m = TMat4<double>::Orthographic(left, right, bottom, top, near, far);
	REQUIRE(m[0] == Approx(0.25));
	REQUIRE(m[5] == Approx(0.5));
	REQUIRE(m[10] == Approx(-0.1));

	REQUIRE(m[12] == Approx(-0.5));
	REQUIRE(m[13] == Approx(-0.5));
	REQUIRE(m[14] == Approx(-0.5));
	REQUIRE(m[15] == Approx(1.0));
}

TEST_CASE("TMat4::Perspective", "[tmat4_perspective]")
{
	SECTION("Basic perspective matrix")
	{
		const double fov = 90.0;
		const double aspect = 1.0;
		const double nearPlane = 0.1;
		const double farPlane = 100.0;

		const auto m = TMat4<double>::Perspective(fov, aspect, nearPlane, farPlane);
		const double cot = 1.0 / Math::Tan(fov * 0.5);

		REQUIRE(m[0] == Approx(cot / aspect));
		REQUIRE(m[5] == Approx(cot));

		REQUIRE(m[10] == Approx((nearPlane + farPlane) / (nearPlane - farPlane)));
		REQUIRE(m[11] == Approx(-1.0));
		REQUIRE(m[14] == Approx((2.0 * nearPlane * farPlane) / (nearPlane - farPlane)));

		REQUIRE(m[1] == Approx(0.0));
		REQUIRE(m[2] == Approx(0.0));
		REQUIRE(m[3] == Approx(0.0));
		REQUIRE(m[4] == Approx(0.0));
		REQUIRE(m[6] == Approx(0.0));
		REQUIRE(m[7] == Approx(0.0));
		REQUIRE(m[8] == Approx(0.0));
		REQUIRE(m[9] == Approx(0.0));
		REQUIRE(m[12] == Approx(0.0));
		REQUIRE(m[13] == Approx(0.0));
		REQUIRE(m[15] == Approx(0.0));
	}

	SECTION("Aspect ratio variation")
	{
		const double fov = 60.0;
		const double aspect = 16.0 / 9.0;
		const double nearPlane = 0.5;
		const double farPlane = 500.0;

		const auto m = TMat4<double>::Perspective(fov, aspect, nearPlane, farPlane);
		const double cot = 1.0 / Math::Tan(fov * 0.5);

		REQUIRE(m[0] == Approx(cot / aspect));
		REQUIRE(m[5] == Approx(cot));

		REQUIRE(m[10] == Approx((nearPlane + farPlane) / (nearPlane - farPlane)));
		REQUIRE(m[14] == Approx((2.0 * nearPlane * farPlane) / (nearPlane - farPlane)));
	}
}

TEST_CASE("TMat4::IsValid", "[tmat4_is_valid]")
{
	const auto identity = TMat4<double>::Identity();
	REQUIRE(identity.IsValid());

	const auto inf = TMat4<double>(Math::TInfinity<double>, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	REQUIRE(!inf.IsValid());
}
