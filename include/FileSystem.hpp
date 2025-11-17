#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "CoreDefines.hpp"

namespace GCore::FileSystem
{
	enum class WriteType : uint8_t
	{
		Append,
		Clear,
		Overwrite
	};

	inline bool FileExists(const std::filesystem::path& filePath_)
	{
		return std::filesystem::exists(filePath_) && std::filesystem::is_regular_file(filePath_);
	}

	inline bool DirExists(const std::filesystem::path& dirPath_)
	{
		return std::filesystem::exists(dirPath_) && std::filesystem::is_directory(dirPath_);
	}

	[[nodiscard]] ErrorCode CreateFile(const std::filesystem::path& filePath_);
	[[nodiscard]] ErrorCode CreateDirectory(const std::filesystem::path& dirPath_);

	[[nodiscard]] ErrorCode ReadFile(const std::filesystem::path& filePath_, std::vector<std::string>& outBuffer_);
	[[nodiscard]] ErrorCode WriteToFile(const std::filesystem::path& filePath_, const std::string& content_, WriteType writeType_ = WriteType::Append);
}
