#include <catch2/catch_all.hpp>

#include "GCore/Math/TMat2.hpp"

using namespace Gadget;

TEST_CASE("TMat2::TMat2", "[tmat2_constructor]")
{
	const TMat2<double> doubleMat2;
	REQUIRE(doubleMat2[0] == 1.0);
	REQUIRE(doubleMat2[1] == 0.0);

	REQUIRE(doubleMat2[2] == 0.0);
	REQUIRE(doubleMat2[3] == 1.0);
}
