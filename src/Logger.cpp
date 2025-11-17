#include "Logger.hpp"

#include <print>

#include "FileSystem.hpp"

using namespace GCore;

static inline Logger::CallbackFunc& GetLoggerFunc() noexcept
{
	static Logger::CallbackFunc func;
	return func;
}

void Logger::Init(CallbackFunc callback_) noexcept
{
	GetLoggerFunc() = std::move(callback_);
}

void Logger::SimpleInit(Mode mode_, Severity minSeverity_, const std::filesystem::path& path_) noexcept
{
	switch (mode_)
	{
		case Mode::StdOut:
			GetLoggerFunc() = [minSeverity_](Severity severity_, std::string message_)
			{
				if (severity_ <= minSeverity_)
				{
					std::println("{}", std::move(message_));
				}
			};

			break;
		case Mode::FileOut:
			GetLoggerFunc() = [path_, minSeverity_](Severity severity_, std::string message_)
			{
				const std::string msg = std::move(message_); // Suppresses an otherwise useful warning
				if (severity_ <= minSeverity_)
				{
					auto _ = FileSystem::WriteToFile(path_, msg);
				}
			};

			break;
		case Mode::StdAndFile:
			GetLoggerFunc() = [path_, minSeverity_](Severity severity_, std::string message_)
			{
				if (severity_ <= minSeverity_)
				{
					auto _ = FileSystem::WriteToFile(path_, message_);
					std::println("{}", std::move(message_));
				}
			};

			break;
		case Mode::None: [[fallthrough]];
		default:
			GetLoggerFunc() = {};
	}
}

void Logger::OnProcessLogMessage_Internal(Severity severity_, std::string message_)
{
	auto& logFunc = GetLoggerFunc();
	if (logFunc)
	{
		logFunc(severity_, std::move(message_));
	}
}
