#include <catch2/catch_all.hpp>

#include <GCore/Random.hpp>

using namespace Gadget;

template <typename T, size_t Size = 100>
[[nodiscard]]
static inline std::array<T, Size> CreateArrayOfRandomValues(Gadget::Random::SeedT seed, T min, T max)
{
	auto engine = Random::Engine(seed);

	auto out = std::array<T, Size>();
	for (auto& v : out)
	{
		v = engine.Range(min, max);
	}

	return out;
}

TEST_CASE("RandomEngine::Range<int>", "[random_engine_range<int>]")
{
	const auto seedZero_1 = CreateArrayOfRandomValues<int>(0, 1, 100);
	const auto seedZero_2 = CreateArrayOfRandomValues<int>(0, 1, 100);

	static_assert(seedZero_1.size() == seedZero_2.size());
	for (size_t i = 0; i < seedZero_1.size(); i++)
	{
		INFO("i = " << i);
		REQUIRE(seedZero_1.at(i) == seedZero_2.at(i)); // Two engines with the same deterministic seed should product the same result
		REQUIRE(seedZero_1.at(i) >= 1);
		REQUIRE(seedZero_1.at(i) <= 100);
	}

	for (size_t i = 1; i < 1024; i++)
	{
		const auto seedN_1 = CreateArrayOfRandomValues<int>(i, 1, 100);

		size_t differenceCount = 0;
		static_assert(seedZero_1.size() == seedN_1.size());
		for (size_t i = 0; i < seedN_1.size(); i++)
		{
			if(seedZero_1.at(i) != seedN_1.at(i))
			{
				differenceCount++;
			}
		}

		INFO("Seed " << i);
		REQUIRE(differenceCount / static_cast<double>(seedN_1.size()) >= 0.9);
	}
}

TEST_CASE("RandomEngine::Range<float>", "[random_engine_range<float>]")
{
	const auto seedZero_1 = CreateArrayOfRandomValues<float>(0, 0.0f, 1.0f);
	const auto seedZero_2 = CreateArrayOfRandomValues<float>(0, 0.0f, 1.0f);

	static_assert(seedZero_1.size() == seedZero_2.size());
	for (size_t i = 0; i < seedZero_1.size(); i++)
	{
		INFO("i = " << i);
		REQUIRE(seedZero_1.at(i) == Catch::Approx(seedZero_2.at(i))); // Two engines with the same deterministic seed should product the same result
		REQUIRE(seedZero_1.at(i) >= 0.0f);
		REQUIRE(seedZero_1.at(i) <= 1.0f);
	}

	for (size_t i = 1; i < 1024; i++)
	{
		const auto seedN_1 = CreateArrayOfRandomValues<float>(i, 0.0f, 1.0f);

		size_t differenceCount = 0;
		static_assert(seedZero_1.size() == seedN_1.size());
		for (size_t i = 0; i < seedN_1.size(); i++)
		{
			if (seedZero_1.at(i) != Catch::Approx(seedN_1.at(i)))
			{
				differenceCount++;
			}
		}

		INFO("Seed " << i);
		REQUIRE(differenceCount / static_cast<double>(seedN_1.size()) >= 0.9);
	}
}
