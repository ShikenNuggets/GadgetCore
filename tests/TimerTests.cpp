#include <thread>

#include <catch2/catch_all.hpp>

#include <GCore/Timer.hpp>

using namespace std::chrono_literals;
using namespace Gadget;
using Catch::Approx;

// TODO - I'm not sure if these are actually a good idea
TEST_CASE("Timer::DeltaSeconds", "[timer_delta_seconds]")
{
	Timer timer;
	REQUIRE(timer.DeltaSeconds() == Approx(0.0));
	REQUIRE(timer.SecondsSinceStart() == Approx(0.0));
	REQUIRE(timer.SecondsSinceLastUpdate() <= Approx(0.001));

	std::this_thread::sleep_for(1ms);

	timer.Update();
	REQUIRE(timer.DeltaSeconds() >= Approx(0.001));
	REQUIRE(timer.SecondsSinceStart() >= Approx(0.001));
	REQUIRE(timer.SecondsSinceLastUpdate() <= Approx(0.001));

	std::this_thread::sleep_for(2ms);
	REQUIRE(timer.SecondsSinceLastUpdate() >= Approx(0.002));

	timer.Update();
	REQUIRE(timer.SecondsSinceStart() >= Approx(0.003));
}
