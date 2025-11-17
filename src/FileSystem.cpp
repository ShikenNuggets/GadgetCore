#include "FileSystem.hpp"

#include <fstream>

using namespace GCore;

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
	filestream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

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

ErrorCode FileSystem::ReadFile(const std::filesystem::path& filePath_, std::vector<std::string>& outBuffer_)
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
