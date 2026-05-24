#include <catch2/catch_all.hpp>

#include <GCore/Utils/Hash.hpp>

using namespace Gadget;

// Note: These are just sanity checks to confirm that the code is actually working
// We're not testing the quality of the algorithms

TEST_CASE("Hash::FastHash32", "[hash_fast_hash_32]")
{
	// Two inputs have the same output
	const auto testA = Hash::FastHash32("hello");
	const auto testB = Hash::FastHash32("hello");
	REQUIRE(testA == testB);

	// Different input has a different output
	const auto testC = Hash::FastHash32("bonjour");
	REQUIRE(testA != testC);

	// Can be used at compile time
	static constexpr auto testD = Hash::FastHash32("one");
	static constexpr auto testE = Hash::FastHash32("one");
	static constexpr auto testF = Hash::FastHash32("onee");
	static_assert(testD == testE);
	static_assert(testD != testF);

	// Compile time and runtime have the same output
	const auto testD_Runtime = Hash::FastHash32("one");
	REQUIRE(testD == testD_Runtime);

	const auto testEmpty = Hash::FastHash32("");
	REQUIRE(testEmpty == Hash::Internal::fnv1a_32_basis);
}

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
	const auto testD_Runtime = Hash::FastHash64("one");
	REQUIRE(testD == testD_Runtime);

	const auto testEmpty = Hash::FastHash64("");
	REQUIRE(testEmpty == Hash::Internal::fnv1a_64_basis);
}

TEST_CASE("Hash::SafeHash64", "[hash_safe_hash_64]")
{
	static constexpr Hash::SipKey key = { .k0 = 0x1234567890ABCDEFULL, .k1 = 0xFEDCBA0987654321ULL };

	// Two inputs have the same output
	const auto testA = Hash::SafeHash64("hello", key);
	const auto testB = Hash::SafeHash64("hello", key);
	REQUIRE(testA == testB);

	// Different input has a different output
	const auto testC = Hash::SafeHash64("bonjour", key);
	REQUIRE(testA != testC);

	// Can be used at compile time
	static constexpr auto testD = Hash::SafeHash64("one", key);
	static constexpr auto testE = Hash::SafeHash64("one", key);
	static constexpr auto testF = Hash::SafeHash64("onee", key);
	static_assert(testD == testE);
	static_assert(testD != testF);

	// Compile time and runtime have the same output
	auto testD_Runtime = Hash::SafeHash64("one", key);
	REQUIRE(testD == testD_Runtime);

	// Same input with a different key has different output
	static constexpr Hash::SipKey key2 = { .k0 = 0xFEDCBA0987654321ULL, .k1 = 0x1234567890ABCDEFULL };
	const auto testA_key2 = Hash::SafeHash64("hello", key2);
	REQUIRE(testA != testA_key2);
}
