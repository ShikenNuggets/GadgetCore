#include "GCore/Utils/UDL.hpp"

#include <catch2/catch_all.hpp>

using namespace GCore::MemoryUDLs;

TEST_CASE("MemoryUDLs::kb", "[memory_udls_kb]")
{
	static_assert(1_kb == 1024);

	REQUIRE(0_kb == 0);
	REQUIRE(1_kb == 1024);
	REQUIRE(2_kb == 2048);
	REQUIRE(4_kb == 4096);
	REQUIRE(8_kb == 8192);
	REQUIRE(16_kb == 16384);
}

TEST_CASE("MemoryUDLs::mb", "[memory_udls_mb]")
{
	REQUIRE(0_mb == 0);
	REQUIRE(1_mb == 1024 * 1024);
	REQUIRE(2_mb == 2 * 1024 * 1024);
	REQUIRE(4_mb == 4 * 1024 * 1024);
	REQUIRE(8_mb == 8 * 1024 * 1024);
	REQUIRE(16_mb == 16 * 1024 * 1024);
}

TEST_CASE("MemoryUDLs::gb", "[memory_udls_gb]")
{
	REQUIRE(0_gb == 0);
	REQUIRE(1_gb == 1024 * 1024 * 1024);
	REQUIRE(2_gb == 2ULL * 1024ULL * 1024ULL * 1024ULL);
	REQUIRE(4_gb == 4ULL * 1024ULL * 1024ULL * 1024ULL);
	REQUIRE(8_gb == 8ULL * 1024ULL * 1024ULL * 1024ULL);
	REQUIRE(16_gb == 16ULL * 1024ULL * 1024ULL * 1024ULL);
}
