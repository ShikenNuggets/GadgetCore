#pragma once

#include <filesystem>
#include <format>
#include <functional>

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

	template<typename... Args>
	inline void Log(Severity severity_, std::format_string<Args...> fmt_, Args&&... args_)
	{
		auto messageStr = std::format(fmt_, std::forward<Args>(args_)...);
		auto finalMessage = std::format("[GCORE][{}] {}", SeverityToString(severity_), messageStr);
		OnProcessLogMessage_Internal(severity_, std::move(finalMessage));
	}
}
