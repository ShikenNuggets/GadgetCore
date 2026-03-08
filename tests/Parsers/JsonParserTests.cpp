#include <catch2/catch_all.hpp>

#include <GCore/Parsers/JsonParser.hpp>

using namespace Gadget;

TEST_CASE("Json::ParseString", "[json_parse_string]")
{
	const char* validStr = R"({ "pi": 3.141, "happy": true })";

	const auto result = Json::ParseString(validStr);
	REQUIRE(result.has_value());
	if (result.has_value())
	{
		const auto& json = result.value();
		REQUIRE(json["pi"] == 3.141);
		REQUIRE(json["happy"] == true);
	}

	const char* invalidStr = "foo";
	const auto result2 = Json::ParseString(invalidStr);
	REQUIRE(!result2.has_value());
}
