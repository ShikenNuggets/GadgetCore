#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat3.hpp"

using namespace Gadget;

TEST_CASE("TMat3::TMat3", "[tmat3_constructor]")
{
	const TMat3<double> doubleMat3;
	REQUIRE(doubleMat3[0] == 1.0);
	REQUIRE(doubleMat3[1] == 0.0);
	REQUIRE(doubleMat3[2] == 0.0);

	REQUIRE(doubleMat3[3] == 0.0);
	REQUIRE(doubleMat3[4] == 1.0);
	REQUIRE(doubleMat3[5] == 0.0);
	
	REQUIRE(doubleMat3[6] == 0.0);
	REQUIRE(doubleMat3[7] == 0.0);
	REQUIRE(doubleMat3[8] == 1.0);
}
