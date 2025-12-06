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
