#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat3.hpp"

using namespace Gadget;
using Catch::Approx;

TEST_CASE("TMat3::TMat3", "[tmat3_constructor]")
{
	const TMat3<double> defaultConstructed;
	const auto identity = TMat3<double>::Identity();

	for (size_t i = 0; i < 3 * 3; ++i)
	{
		REQUIRE(defaultConstructed[i] == identity[i]);
	}
}

TEST_CASE("TMat3::TMat3(T...)", "[tmat3_constructor_t]")
{
	const auto doubleMat3 = TMat3<double>(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
	for(size_t i = 0; i < 3 * 3; ++i)
	{
		REQUIRE(doubleMat3[i] == static_cast<double>(i));
	}
}

TEST_CASE("TMat3::operator[]", "[tmat3_operator_array]")
{
	auto mat = TMat3<double>::Identity();
	mat[0] = 0.0;
	mat[1] = 1.0;
	mat[2] = 2.0;
	mat[3] = 3.0;
	mat[4] = 4.0;
	mat[5] = 5.0;
	mat[6] = 6.0;
	mat[7] = 7.0;
	mat[8] = 8.0;

	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(mat[i] == static_cast<double>(i));
	}

	REQUIRE_THROWS(mat[-1]);
	REQUIRE_THROWS(mat[TMat3<double>::Size()]);
}

TEST_CASE("TMat3::operator*(TMat3)", "[tmat3_operator_*_tmat3]")
{
	const auto identity = TMat3<double>::Identity();
	const auto zero = TMat3<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	const auto testMat1 = TMat3<double>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
	const auto testMat2 = TMat3<double>(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);

	const auto resultA = identity * testMat1;
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(resultA[i] == testMat1[i]);
	}

	const auto resultB = testMat1 * identity;
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(resultB[i] == testMat1[i]);
	}

	const auto resultC = zero * testMat1;
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(resultC[i] == zero[i]);
	}

	const auto resultD = testMat1 * testMat2;
	REQUIRE(resultD[0] ==  90.0);
	REQUIRE(resultD[1] ==  114.0);
	REQUIRE(resultD[2] ==  138.0);

	REQUIRE(resultD[3] ==  54.0);
	REQUIRE(resultD[4] ==  69.0);
	REQUIRE(resultD[5] ==  84.0);

	REQUIRE(resultD[6] == 18.0);
	REQUIRE(resultD[7] == 24.0);
	REQUIRE(resultD[8] ==  30.0);
}

TEST_CASE("TMat3::operator*=(TMat3)", "[tmat3_operator_*=_tmat3]")
{
	const auto identity = TMat3<double>::Identity();
	const auto zero = TMat3<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	const auto testMat1 = TMat3<double>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
	const auto testMat2 = TMat3<double>(9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0);
	
	const auto truthA = identity * testMat1;
	auto resultA = identity;
	resultA *= testMat1;
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(resultA[i] == truthA[i]);
	}

	const auto truthB = testMat1 * identity;
	auto resultB = testMat1;
	resultB *= identity;
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(resultB[i] == truthB[i]);
	}

	const auto truthC = zero * testMat1;
	auto resultC = zero;
	resultC *= testMat1;
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(resultC[i] == truthC[i]);
	}

	const auto truthD = testMat1 * testMat2;
	auto resultD = testMat1;
	resultD *= testMat2;
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(resultD[i] == truthD[i]);
	}
}

TEST_CASE("TMat3::Identity", "[tmat3_identity]")
{
	const auto identity = TMat3<double>::Identity();
	REQUIRE(identity[0] == 1.0);
	REQUIRE(identity[1] == 0.0);
	REQUIRE(identity[2] == 0.0);

	REQUIRE(identity[3] == 0.0);
	REQUIRE(identity[4] == 1.0);
	REQUIRE(identity[5] == 0.0);

	REQUIRE(identity[6] == 0.0);
	REQUIRE(identity[7] == 0.0);
	REQUIRE(identity[8] == 1.0);
}

TEST_CASE("TMat3::Determinant", "[tmat3_determinant]")
{
	const auto identity = TMat3<double>::Identity();
	REQUIRE(identity.Determinant() == Approx(1.0));

	auto m = TMat3<double>(1.0, 0.0, 5.0, 2.0, 1.0, 6.0, 3.0, 4.0, 0.0);
	REQUIRE(m.Determinant() == Approx(1.0));

	m = TMat3<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	REQUIRE(m.Determinant() == 0.0);

	m = TMat3<double>(-2.0, 3.0, 1.0, 4.0, -5.0, 2.0, 0.0, 1.0, -1.0);
	REQUIRE(m.Determinant() == Approx(10.0));
}

TEST_CASE("TMat3::Inverse", "[tmat3_inverse]")
{
	const auto identity = TMat3<double>::Identity();
	const auto invId = identity.Inverse();
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(invId[i] == identity[i]);
	}

	auto m = TMat3<double>(1.0, 0.0, 5.0, 2.0, 1.0, 6.0, 3.0, 4.0, 0.0).Inverse();
	REQUIRE(m[0] == Approx(-24.0));
	REQUIRE(m[1] == Approx(20.0));
	REQUIRE(m[2] == Approx(-5.0));
	REQUIRE(m[3] == Approx(18.0));
	REQUIRE(m[4] == Approx(-15.0));
	REQUIRE(m[5] == Approx(4.0));
	REQUIRE(m[6] == Approx(5.0));
	REQUIRE(m[7] == Approx(-4.0));
	REQUIRE(m[8] == Approx(1.0));

	// TODO - Matrix * Inverse == Identity

	m = TMat3<double>(2.0, 1.0, 0.0, 4.0, 2.0, 0.0, 1.0, 0.0, 0.0).Inverse();
	for (size_t i = 0; i < TMat3<double>::Size(); ++i)
	{
		REQUIRE(m[i] == 0.0);
	}
}

TEST_CASE("TMat3::IsValid", "[tmat3_is_valid]")
{
	const auto identity = TMat3<double>::Identity();
	REQUIRE(identity.IsValid());

	const auto inf = TMat3<double>(Math::TInfinity<double>, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	REQUIRE(!inf.IsValid());
}
