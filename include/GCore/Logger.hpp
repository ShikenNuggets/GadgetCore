#pragma once

#include <filesystem>
#include <format>
#include <functional>
#include <source_location>

namespace Gadget::Logger
{
	enum Severity : uint8_t
	{
		None,
		FatalError,
		Error,
		Warning,
		Info,
		Verbose
	};

	enum class Mode : uint8_t
	{
		None,
		StdOut,
		FileOut,
		StdAndFile
	};

	using CallbackFunc = std::function<void(Severity, std::string)>;

	void Init(CallbackFunc callback_) noexcept;
	void SimpleInit(Mode mode_, Severity minSeverity_, const std::filesystem::path& path_) noexcept;

	// Do not call this directly
	void OnProcessLogMessage_Internal(Severity severity_, std::string message_);

	inline constexpr const char* SeverityToString(Severity severity_)
	{
		switch (severity_)
		{
			case Severity::FatalError:
				return "FATAL";
			case Severity::Error:
				return "ERROR";
			case Severity::Warning:
				return "WARNING";
			case Severity::Info:
				return "INFO";
			case Severity::Verbose:
				return "VERBOSE";
			default:
				break;
		}

		return "";
	}

	static constexpr const char* value = SeverityToString(Logger::Severity::None);

	inline void Log(Severity severity, std::string_view message, std::source_location sourceLocation = std::source_location::current())
	{
		auto fmtMessage = std::format("[GCORE][{}][{}:{}] {}",
			SeverityToString(severity),
			std::filesystem::path(sourceLocation.file_name()).filename().string(),
			sourceLocation.line(),
			message
		);
		
		OnProcessLogMessage_Internal(severity, std::move(fmtMessage));
	}
}

#ifndef GADGET_LOG
	#define GADGET_LOG(severity, message, ...) { Gadget::Logger::Log(Gadget::Logger::Severity::severity, std::format(message, ##__VA_ARGS__), std::source_location::current()); }
#endif // !GADGET_LOG

#ifndef GADGET_LOG_INFO
	#define GADGET_LOG_INFO(message, ...) GADGET_LOG(Info, message, ##__VA_ARGS__)
#endif // !GADGET_LOG_INFO

#ifndef GADGET_LOG_WARNING
	#define GADGET_LOG_WARNING(message, ...) GADGET_LOG(Warning, message, ##__VA_ARGS__)
#endif // !GADGET_LOG_WARNING

#ifndef GADGET_LOG_ERROR
	#define GADGET_LOG_ERROR(message, ...) GADGET_LOG(Error, message, ##__VA_ARGS__)
#endif // !GADGET_LOG_ERROR
