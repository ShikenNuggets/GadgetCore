#include <catch2/catch_all.hpp>

#include <GCore/Math/Quaternion.hpp>

using namespace Gadget;

TEST_CASE("TQuat::TQuat", "[tquat_constructor]")
{
	const auto defaultInit = TQuat<double>();
	REQUIRE(defaultInit.w == 1.0);
	REQUIRE(defaultInit.x == 0.0);
	REQUIRE(defaultInit.y == 0.0);
	REQUIRE(defaultInit.z == 0.0);

	const auto customInit = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(customInit.w == 1.0);
	REQUIRE(customInit.x == 2.0);
	REQUIRE(customInit.y == 3.0);
	REQUIRE(customInit.z == 4.0);
}

TEST_CASE("TQuat::Identity", "[tquat_identity]")
{
	const TQuat<double> doubleQuat = TQuat<double>::Identity();
	REQUIRE(doubleQuat.w == 1.0);
	REQUIRE(doubleQuat.x == 0.0);
	REQUIRE(doubleQuat.y == 0.0);
	REQUIRE(doubleQuat.z == 0.0);
}

TEST_CASE("TQuat::*", "[tquat_*]")
{
	const auto identityTimesQ = TQuat<double>::Identity() * TQuat<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(identityTimesQ.w == 1.0);
	REQUIRE(identityTimesQ.x == 2.0);
	REQUIRE(identityTimesQ.y == 3.0);
	REQUIRE(identityTimesQ.z == 4.0);

	const auto qTimesIdentity = TQuat<double>(1.0, 2.0, 3.0, 4.0) * TQuat<double>::Identity();
	REQUIRE(qTimesIdentity.w == 1.0);
	REQUIRE(qTimesIdentity.x == 2.0);
	REQUIRE(qTimesIdentity.y == 3.0);
	REQUIRE(qTimesIdentity.z == 4.0);

	// TODO - q * inverse(q)

	const auto multTest = TQuat<double>(1.0, 2.0, 3.0, 4.0) * TQuat<double>(5.0, 6.0, 7.0, 8.0);
	REQUIRE(multTest.w == -60.0);
	REQUIRE(multTest.x == 12.0);
	REQUIRE(multTest.y == 30.0);
	REQUIRE(multTest.z == 24.0);

	// Test associativity
	const auto assocTestA = TQuat<double>(0.3, -0.5, 0.1, 0.8);
	const auto assocTestB = TQuat<double>(0.1, 0.3, 0.6, 0.8);
	const auto assocTestC = TQuat<double>(-0.2, 0.4, 0.2, 0.9);

	const auto leftMult = (assocTestA * assocTestB) * assocTestC;
	const auto rightMult = assocTestA * (assocTestB * assocTestC);

	REQUIRE(leftMult.w == Math::Approx(rightMult.w));
	REQUIRE(leftMult.x == Math::Approx(rightMult.x));
	REQUIRE(leftMult.y == Math::Approx(rightMult.y));
	REQUIRE(leftMult.z == Math::Approx(rightMult.z));
}

TEST_CASE("TQuat::*TVec3", "[tquat_*_tvec3]")
{
	const auto identityRotation = TQuat<double>::Identity() * TVec3<double>(1.0, -2.0, 3.0);
	REQUIRE(identityRotation.x == Math::Approx(1.0));
	REQUIRE(identityRotation.y == Math::Approx(-2.0));
	REQUIRE(identityRotation.z == Math::Approx(3.0));

	const auto rotationX90 = TQuat<double>(Math::Cos(45.0), Math::Sin(45.0), 0.0, 0.0) * TVec3(0.0, 1.0, 0.0);
	REQUIRE(rotationX90.x == Math::Approx(0.0));
	REQUIRE(rotationX90.y == Math::Approx(0.0));
	REQUIRE(rotationX90.z == Math::Approx(1.0));

	const auto rotationZ180 = TQuat<double>(0.0, 0.0, 0.0, 1.0) * TVec3<double>(1.0, 2.0, 3.0);
	REQUIRE(rotationZ180.x == Math::Approx(-1.0));
	REQUIRE(rotationZ180.y == Math::Approx(-2.0));
	REQUIRE(rotationZ180.z == Math::Approx(3.0));
}

TEST_CASE("TQuat::*=", "[tquat_*=]")
{
	auto identityTimesQ = TQuat<double>::Identity();
	identityTimesQ *= TQuat<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(identityTimesQ.w == 1.0);
	REQUIRE(identityTimesQ.x == 2.0);
	REQUIRE(identityTimesQ.y == 3.0);
	REQUIRE(identityTimesQ.z == 4.0);

	auto qTimesIdentity = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	qTimesIdentity *= TQuat<double>::Identity();
	REQUIRE(qTimesIdentity.w == 1.0);
	REQUIRE(qTimesIdentity.x == 2.0);
	REQUIRE(qTimesIdentity.y == 3.0);
	REQUIRE(qTimesIdentity.z == 4.0);

	// TODO - q *= inverse(q)

	auto multTest = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	multTest *= TQuat<double>(5.0, 6.0, 7.0, 8.0);
	REQUIRE(multTest.w == -60.0);
	REQUIRE(multTest.x == 12.0);
	REQUIRE(multTest.y == 30.0);
	REQUIRE(multTest.z == 24.0);

	// Test associativity
	const auto assocTestA = TQuat<double>(0.3, -0.5, 0.1, 0.8);
	const auto assocTestB = TQuat<double>(0.1, 0.3, 0.6, 0.8);
	const auto assocTestC = TQuat<double>(-0.2, 0.4, 0.2, 0.9);

	auto leftMult = (assocTestA * assocTestB);
	leftMult *= assocTestC;

	auto rightMult = assocTestA;
	rightMult *= (assocTestB * assocTestC);

	REQUIRE(leftMult.w == Math::Approx(rightMult.w));
	REQUIRE(leftMult.x == Math::Approx(rightMult.x));
	REQUIRE(leftMult.y == Math::Approx(rightMult.y));
	REQUIRE(leftMult.z == Math::Approx(rightMult.z));
}
