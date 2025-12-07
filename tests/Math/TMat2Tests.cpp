#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat2.hpp"

using namespace Gadget;

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
