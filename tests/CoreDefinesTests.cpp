#include <catch2/catch_all.hpp>

#include <GCore/CoreDefines.hpp>

using namespace Gadget;

TEST_CASE("GetErrorCodeString", "[get_error_code_string]")
{
	std::string errorCodeStr = GetErrorCodeString(ErrorCode::OK);
	REQUIRE(errorCodeStr == "OK");

	errorCodeStr = GetErrorCodeString(ErrorCode::InvalidArgs);
	REQUIRE(errorCodeStr == "InvalidArgs");

	errorCodeStr = GetErrorCodeString(ErrorCode::ErrorCode_MAX);
	REQUIRE(errorCodeStr == "UnknownErrorCode");
}
