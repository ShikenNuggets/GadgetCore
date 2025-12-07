#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat4.hpp"

using namespace Gadget;

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
