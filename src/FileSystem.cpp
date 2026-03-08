#include "FileSystem.hpp"

#include <fstream>

using namespace Gadget;

ErrorCode FileSystem::CreateDirectory(const std::filesystem::path& dirPath_)
{
	if (DirExists(dirPath_))
	{
		return ErrorCode::OK;
	}

	return std::filesystem::create_directory(dirPath_) ? ErrorCode::OK : ErrorCode::FileIO;
}

ErrorCode FileSystem::CreateFile(const std::filesystem::path& filePath_)
{
	if (FileExists(filePath_))
	{
		return ErrorCode::OK;
	}

	std::filesystem::path dirPath = filePath_;
	dirPath.remove_filename();
	auto err = CreateDirectory(dirPath);
	if (err != ErrorCode::OK)
	{
		return err;
	}

	std::fstream filestream;
	filestream.exceptions(std::fstream::failbit | std::fstream::badbit);

	try
	{
		filestream.open(filePath_, std::ios::out | std::ios_base::trunc);
	}
	catch (std::system_error& e)
	{
		return ErrorCode::FileIO;
	}

	filestream.flush();
	filestream.close();
	return ErrorCode::OK;
}

ErrorCode FileSystem::ReadFileLines(const std::filesystem::path& filePath_, std::vector<std::string>& outBuffer_)
{
	std::fstream fileStream;
	fileStream.open(filePath_, std::ios::in);
	if (!fileStream.is_open())
	{
		return ErrorCode::FileIO;
	}

	std::string line;
	while(std::getline(fileStream, line))
	{
		outBuffer_.push_back(std::move(line));
	}
	outBuffer_.shrink_to_fit();

	fileStream.close();
	return ErrorCode::OK;
}

std::expected<std::vector<std::string>, ErrorCode> FileSystem::ReadFileLines(const std::filesystem::path& filePath_)
{
	std::vector<std::string> buffer;
	const auto result = ReadFileLines(filePath_, buffer);
	if (result != ErrorCode::OK)
	{
		return std::unexpected(result);
	}

	return buffer;
}

std::expected<std::string, ErrorCode> FileSystem::ReadFileToString(const std::filesystem::path& filePath)
{
	const auto result = ReadFileLines(filePath);
	if (!result.has_value())
	{
		return std::unexpected(result.error());
	}

	std::string outStr;
	for (const auto& str : result.value())
	{
		outStr += str + "\n";
	}

	return outStr;
}

[[nodiscard]] std::expected<std::vector<uint8_t>, ErrorCode> FileSystem::ReadFileRaw(const std::filesystem::path& filePath)
{
	auto fileStream = std::ifstream(filePath, std::ios::binary);
	if (!fileStream.is_open())
	{
		return std::unexpected(ErrorCode::FileIO);
	}

	std::vector<uint8_t> rawData = { std::istreambuf_iterator<char>(fileStream), {} }; // TODO - this is not particularly efficient
	return rawData;
}

ErrorCode FileSystem::WriteToFile(const std::filesystem::path& filePath_, const std::string& content_, WriteType writeType_)
{
	auto err = CreateFile(filePath_);
	if (err != ErrorCode::OK)
	{
		return err;
	}

	std::fstream filestream;

	switch (writeType_)
	{
		case WriteType::Append:
			filestream.open(filePath_, std::fstream::out | std::fstream::app);
			break;
		case WriteType::Clear:
			filestream.open(filePath_, std::ios::out | std::ios_base::trunc);
			break;
		case WriteType::Overwrite:
			filestream.open(filePath_, std::ios::out);
			break;
	}

	if (!filestream.is_open())
	{
		return ErrorCode::FileIO;
	}

	filestream << content_;
	filestream.close();

	if (!filestream)
	{
		return ErrorCode::FileIO;
	}

	return ErrorCode::OK;
}
