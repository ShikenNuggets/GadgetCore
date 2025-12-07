#include <catch2/catch_all.hpp>

#include <GCore/Math/Quaternion.hpp>

using namespace Gadget;
using Catch::Approx;

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

	REQUIRE(leftMult.w == Approx(rightMult.w));
	REQUIRE(leftMult.x == Approx(rightMult.x));
	REQUIRE(leftMult.y == Approx(rightMult.y));
	REQUIRE(leftMult.z == Approx(rightMult.z));
}

TEST_CASE("TQuat::*TVec3", "[tquat_*_tvec3]")
{
	const auto identityRotation = TQuat<double>::Identity() * TVec3<double>(1.0, -2.0, 3.0);
	REQUIRE(identityRotation.x == Approx(1.0));
	REQUIRE(identityRotation.y == Approx(-2.0));
	REQUIRE(identityRotation.z == Approx(3.0));

	const auto rotationX90 = TQuat<double>(Math::Cos(45.0), Math::Sin(45.0), 0.0, 0.0) * TVec3(0.0, 1.0, 0.0);
	REQUIRE(rotationX90.x == Approx(0.0));
	REQUIRE(rotationX90.y == Approx(0.0));
	REQUIRE(rotationX90.z == Approx(1.0));

	const auto rotationZ180 = TQuat<double>(0.0, 0.0, 0.0, 1.0) * TVec3<double>(1.0, 2.0, 3.0);
	REQUIRE(rotationZ180.x == Approx(-1.0));
	REQUIRE(rotationZ180.y == Approx(-2.0));
	REQUIRE(rotationZ180.z == Approx(3.0));
}

TEST_CASE("TQuat::*T", "[tquat_operator_*t]")
{
	constexpr auto w = 1.0;
	constexpr auto x = 2.0;
	constexpr auto y = 3.0;
	constexpr auto z = 4.0;

	const auto multTest = TQuat<double>(w, x, y, z) * 5.0;
	REQUIRE(multTest.w == 5.0);
	REQUIRE(multTest.x == 10.0);
	REQUIRE(multTest.y == 15.0);
	REQUIRE(multTest.z == 20.0);

	const auto multTest2 = 5.0 * TQuat<double>(w, x, y, z);
	REQUIRE(multTest.w == multTest2.w);
	REQUIRE(multTest.x == multTest2.x);
	REQUIRE(multTest.y == multTest2.y);
	REQUIRE(multTest.z == multTest2.z);
}

TEST_CASE("TVec4::/T", "[tvec4_operator_/t]")
{
	const auto divTest = TQuat<double>(3.0, 6.0, 9.0, 12.0) / 3.0;
	REQUIRE(divTest.w == 1.0);
	REQUIRE(divTest.x == 2.0);
	REQUIRE(divTest.y == 3.0);
	REQUIRE(divTest.z == 4.0);
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

	REQUIRE(leftMult.w == Approx(rightMult.w));
	REQUIRE(leftMult.x == Approx(rightMult.x));
	REQUIRE(leftMult.y == Approx(rightMult.y));
	REQUIRE(leftMult.z == Approx(rightMult.z));
}

TEST_CASE("TQuat::*=T", "[tquat_operator_*=t]")
{
	auto multEqualTest = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	multEqualTest *= 5.0;
	REQUIRE(multEqualTest.w == 5.0);
	REQUIRE(multEqualTest.x == 10.0);
	REQUIRE(multEqualTest.y == 15.0);
	REQUIRE(multEqualTest.z == 20.0);
}

TEST_CASE("TVec4::/=T", "[tvec4_operator_/=t]")
{
	auto divTest = TQuat<double>(3.0, 6.0, 9.0, 12.0);
	divTest /= 3.0;
	REQUIRE(divTest.w == 1.0);
	REQUIRE(divTest.x == 2.0);
	REQUIRE(divTest.y == 3.0);
	REQUIRE(divTest.z == 4.0);
}

TEST_CASE("TQuat::SquaredMagnitude", "[tquat_squared_magnitude]")
{
	auto magTest = TQuat<double>(4.0, 4.0, 4.0, 4.0);
	REQUIRE(magTest.SquaredMagnitude() == 64.0);
}

TEST_CASE("TQuat::Magnitude", "[tquat_magnitude]")
{
	auto magTest = TQuat<double>(4.0, 4.0, 4.0, 4.0);
	REQUIRE(magTest.Magnitude() == Math::Sqrt(64.0));

	auto magTest2 = TQuat<double>(0.0, 0.0, 0.0, 0.0);
	REQUIRE(magTest2.Magnitude() == 0.0);
}

TEST_CASE("TQuat::Normal", "[tquat_normal]")
{
	auto normalTest = TQuat<double>(4.0, 4.0, 4.0, 4.0);
	auto normal = normalTest.Normal();
	const auto expected = normalTest / Math::Sqrt(64.0);
	REQUIRE(Math::IsNear(normal.Magnitude(), 1.0));
	REQUIRE(Math::IsNear(normal.w, expected.w));
	REQUIRE(Math::IsNear(normal.x, expected.x));
	REQUIRE(Math::IsNear(normal.y, expected.y));
	REQUIRE(Math::IsNear(normal.z, expected.z));
}

TEST_CASE("TQuat::Dot", "[tquat_dot]")
{
	REQUIRE(TQuat<double>::Dot(TQuat<double>(1.0, 2.0, 3.0, 4.0), TQuat<double>(5.0, 6.0, 7.0, 8.0)) == Approx(70.0));
	REQUIRE(TQuat<double>::Dot(TQuat<double>(0.0, 0.0, 0.0, 0.0), TQuat<double>(3.0, 2.0, 1.0, 4.0)) == Approx(0.0));
	REQUIRE(TQuat<double>::Dot(TQuat<double>(-1.0, 2.0, -3.0, 4.0), TQuat<double>(-4.0, 3.0, -2.0, 1.0)) == Approx(20.0));
}

TEST_CASE("TQuat::Lerp", "[tquat_lerp]")
{
	const auto q1 = TQuat<double>(0.0, 0.0, 0.0, 1.0);
	const auto q2 = TQuat<double>(0.0, 1.0, 0.0, 0.0);

	const auto q1Norm = q1.Normal();
	auto result = TQuat<double>::Lerp(q1, q2, 0.0);
	REQUIRE(result.w == Approx(q1Norm.w));
	REQUIRE(result.x == Approx(q1Norm.x));
	REQUIRE(result.y == Approx(q1Norm.y));
	REQUIRE(result.z == Approx(q1Norm.z));

	const auto q2Norm = q2.Normal();
	result = TQuat<double>::Lerp(q1, q2, 1.0);
	REQUIRE(result.w == Approx(q2Norm.w));
	REQUIRE(result.x == Approx(q2Norm.x));
	REQUIRE(result.y == Approx(q2Norm.y));
	REQUIRE(result.z == Approx(q2Norm.z));

	result = TQuat<double>::Lerp(q1, q2, 0.5);
	REQUIRE(result.w == Approx(0.0));
	REQUIRE(result.x == Approx(0.70710678118654746));
	REQUIRE(result.y == Approx(0.0));
	REQUIRE(result.z == Approx(0.70710678118654746));

	const auto q3 = TQuat<double>::Identity();
	const auto q4 = TQuat<double>(-0.5, -0.866025403784, 0.0, 0.0);
	REQUIRE(TQuat<double>::Dot(q3, q4) < 0.0);

	result = TQuat<double>::Lerp(q3, q4, 0.5);
	REQUIRE(result.w == Approx(0.86602540378454829));
	REQUIRE(result.x == Approx(0.49999999999980999));
	REQUIRE(result.y == Approx(0.0));
	REQUIRE(result.z == Approx(0.0));
}

TEST_CASE("TQuat::IsNear", "[tquat_is_near]")
{
	const auto testA = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	const auto testB = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	const auto testC = TQuat<double>(1.0001, 2.0001, 3.1, 3.9995);

	REQUIRE(testA.IsNear(testA));
	REQUIRE(testA.IsNear(testB));
	REQUIRE(!testA.IsNear(testC));

	REQUIRE(testB.IsNear(testB));
	REQUIRE(!testB.IsNear(testC));

	REQUIRE(testC.IsNear(testC));
}

TEST_CASE("TQuat::IsValid", "[tquat_is_valid]")
{
	const auto valid = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	const auto invalid = TQuat<double>(Math::TInfinity<double>, 0.0, -1.0, -2.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
