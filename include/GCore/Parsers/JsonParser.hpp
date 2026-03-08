#pragma once

#include <expected>
#include <filesystem>
#include <optional>

#include <nlohmann/json.hpp>

#include "GCore/CoreDefines.hpp"

namespace Gadget::Json
{
	[[nodiscard]] std::optional<nlohmann::json> ParseString(std::string_view sourceStr);
	[[nodiscard]] std::expected<nlohmann::json, ErrorCode> ParseFile(const std::filesystem::path& filePath);
}
