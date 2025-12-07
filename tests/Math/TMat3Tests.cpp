#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat3.hpp"

using namespace Gadget;

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
