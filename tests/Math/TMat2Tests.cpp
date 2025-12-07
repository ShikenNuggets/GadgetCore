#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat2.hpp"

using namespace Gadget;
using Catch::Approx;

TEST_CASE("TMat2::TMat2", "[tmat2_constructor]")
{
	const TMat2<double> defaultConstructed;
	const auto identity = TMat2<double>::Identity();

	for (size_t i = 0; i < TMat2<double>::Size(); ++i)
	{
		REQUIRE(defaultConstructed[i] == identity[i]);
	}
}

TEST_CASE("TMat2::TMat2(T...)", "[tmat2_constructor_t]")
{
	const auto doubleMat2 = TMat2<double>(0.0, 1.0, 2.0, 3.0);
	for(size_t i = 0; i < TMat2<double>::Size(); ++i)
	{
		REQUIRE(doubleMat2[i] == static_cast<double>(i));
	}
}

TEST_CASE("TMat2::operator[]", "[tmat2_operator_array]")
{
	auto mat = TMat2<double>::Identity();
	mat[0] = 0.0;
	mat[1] = 1.0;
	mat[2] = 2.0;
	mat[3] = 3.0;

	for (size_t i = 0; i < TMat2<double>::Size(); ++i)
	{
		REQUIRE(mat[i] == static_cast<double>(i));
	}

	REQUIRE_THROWS(mat[-1]);
	REQUIRE_THROWS(mat[TMat2<double>::Size()]);
}

TEST_CASE("TMat2::Identity", "[tmat2_identity]")
{
	const auto identity = TMat2<double>::Identity();
	REQUIRE(identity[0] == 1.0);
	REQUIRE(identity[1] == 0.0);

	REQUIRE(identity[2] == 0.0);
	REQUIRE(identity[3] == 1.0);
}

TEST_CASE("TMat2::Determinant", "[tmat2_determinant]")
{
	const auto identity = TMat2<double>::Identity();
	REQUIRE(identity.Determinant() == Approx(1.0));

	auto m = TMat2<double>(4.0, 3.0, 6.0, 3.0);
	REQUIRE(m.Determinant() == Approx(-6.0));

	m = TMat2<double>(0.0, 0.0, 0.0, 0.0);
	REQUIRE(m.Determinant() == 0.0);

	m = TMat2<double>(-2.0, 3.0, 4.0, 5.0);
	REQUIRE(m.Determinant() == Approx(-22.0));
}

TEST_CASE("TMat2::Inverse", "[tmat2_inverse]")
{
	const auto identity = TMat2<double>::Identity();
	const auto invId = identity.Inverse();
	for (size_t i = 0; i < TMat2<double>::Size(); ++i)
	{
		REQUIRE(invId[i] == identity[i]);
	}

	auto m = TMat2<double>(4.0, 7.0, 2.0, 6.0).Inverse();
	REQUIRE(m[0] == Approx(0.6));
	REQUIRE(m[1] == Approx(-0.7));
	REQUIRE(m[2] == Approx(-0.2));
	REQUIRE(m[3] == Approx(0.4));

	// TODO - Matrix * Inverse == Identity

	m = TMat2<double>(2.0, 4.0, 1.0, 2.0).Inverse();
	REQUIRE(m[0] == 0.0);
	REQUIRE(m[1] == 0.0);
	REQUIRE(m[2] == 0.0);
	REQUIRE(m[3] == 0.0);
}
