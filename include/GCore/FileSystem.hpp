#pragma once

#include <expected>
#include <filesystem>
#include <string>
#include <vector>

#include "CoreDefines.hpp"

namespace Gadget::FileSystem
{
	enum class WriteType : uint8_t
	{
		Append,
		Clear,
		Overwrite
	};

	inline bool FileExists(const std::filesystem::path& filePath_) noexcept
	{
		std::error_code err;
		return std::filesystem::exists(filePath_, err) && std::filesystem::is_regular_file(filePath_, err);
	}

	inline bool DirExists(const std::filesystem::path& dirPath_) noexcept
	{
		std::error_code err;
		return std::filesystem::exists(dirPath_, err) && std::filesystem::is_directory(dirPath_, err);
	}

	[[nodiscard]] ErrorCode CreateFile(const std::filesystem::path& filePath_) noexcept;
	[[nodiscard]] ErrorCode CreateDirectory(const std::filesystem::path& dirPath_) noexcept;

	[[nodiscard]] ErrorCode ReadFileLines(const std::filesystem::path& filePath_, std::vector<std::string>& outBuffer_);
	[[nodiscard]] std::expected<std::vector<std::string>, ErrorCode> ReadFileLines(const std::filesystem::path& filePath_);
	[[nodiscard]] std::expected<std::string, ErrorCode> ReadFileToString(const std::filesystem::path& filePath);
	[[nodiscard]] std::expected<std::vector<uint8_t>, ErrorCode> ReadFileRaw(const std::filesystem::path& filePath);

	[[nodiscard]] ErrorCode WriteToFile(const std::filesystem::path& filePath_, const std::string& content_, WriteType writeType_ = WriteType::Append);
}
