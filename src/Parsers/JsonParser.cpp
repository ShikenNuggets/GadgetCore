#include "Parsers/JsonParser.hpp"

#include "FileSystem.hpp"
#include "Logger.hpp"

using namespace Gadget;

std::optional<nlohmann::json> Json::ParseString(std::string_view sourceStr)
{
	if (sourceStr.empty())
	{
		GADGET_LOG_WARNING("Tried to parse an empty string as Json");
		return std::nullopt;
	}

	try
	{
		return nlohmann::json::parse(sourceStr);
	}
	catch (const nlohmann::json::parse_error& e)
	{
		GADGET_LOG_ERROR("Failed to parse {} into JSON. Error: {} - error ID {} at byte {}", sourceStr, e.what(), e.id, e.byte);
	}
	catch (...)
	{
		GADGET_LOG_ERROR("Unknown error occured trying to parse: \"{}\"", sourceStr);
	}

	return std::nullopt;
}

std::expected<nlohmann::json, ErrorCode> Json::ParseFile(const std::filesystem::path& filePath)
{
	const auto fileResult = FileSystem::ReadFileToString(filePath);
	if (!fileResult.has_value())
	{
		return std::unexpected(fileResult.error());
	}

	const auto parseResult = ParseString(fileResult.value());
	if (!parseResult.has_value())
	{
		return std::unexpected(ErrorCode::ParseError);
	}

	return parseResult.value();
}
