#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat4.hpp"

using namespace Gadget;

TEST_CASE("TMat4::TMat4", "[tmat4_constructor]")
{
	const TMat4<double> doubleMat4;
	REQUIRE(doubleMat4[0] == 1.0);
	REQUIRE(doubleMat4[1] == 0.0);
	REQUIRE(doubleMat4[2] == 0.0);
	REQUIRE(doubleMat4[3] == 0.0);

	REQUIRE(doubleMat4[4] == 0.0);
	REQUIRE(doubleMat4[5] == 1.0);
	REQUIRE(doubleMat4[6] == 0.0);
	REQUIRE(doubleMat4[7] == 0.0);
	
	REQUIRE(doubleMat4[8] == 0.0);
	REQUIRE(doubleMat4[9] == 0.0);
	REQUIRE(doubleMat4[10] == 1.0);
	REQUIRE(doubleMat4[11] == 0.0);
	
	REQUIRE(doubleMat4[12] == 0.0);
	REQUIRE(doubleMat4[13] == 0.0);
	REQUIRE(doubleMat4[14] == 0.0);
	REQUIRE(doubleMat4[15] == 1.0);
}
