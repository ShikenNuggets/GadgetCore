#include <catch2/catch_all.hpp>

#include <GCore/Utils/Hash.hpp>

using namespace Gadget;

// Note: These are just sanity checks to confirm that the code is actually working
// We're not testing the quality of the algorithm

TEST_CASE("Hash::FastHash64", "[hash_fast_hash_64]")
{
	// Two inputs have the same output
	const auto testA = Hash::FastHash64("hello");
	const auto testB = Hash::FastHash64("hello");
	REQUIRE(testA == testB);

	// Different input has a different output
	const auto testC = Hash::FastHash64("bonjour");
	REQUIRE(testA != testC);

	// Can be used at compile time
	static constexpr auto testD = Hash::FastHash64("one");
	static constexpr auto testE = Hash::FastHash64("one");
	static constexpr auto testF = Hash::FastHash64("onee");
	static_assert(testD == testE);
	static_assert(testD != testF);

	// Compile time and runtime have the same output
	auto testD_Runtime = Hash::FastHash64("one");
	REQUIRE(testD == testD_Runtime);
}
