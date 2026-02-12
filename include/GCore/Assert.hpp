#pragma once

#include <format>
#include <source_location>
#include <string_view>

namespace Gadget
{
	void PopupErrorMessage(std::string_view title, std::string_view message);

	inline void Assert(bool condition, std::string_view message, std::source_location sourceLocation = std::source_location::current())
	{
		if (!condition)
		{
			const auto fmtMessage = std::format("{}\n\n{}:{}", message, std::filesystem::path(sourceLocation.file_name()).filename().string(), sourceLocation.line());
			#ifdef GADGET_BUILD_NO_ASSERT
				Logger::Log(Logger::Fatal, "Assertion Failed: ", fmtMessage);
			#else
				PopupErrorMessage("Assertion Failed!", fmtMessage);
			#endif
		}
	}

	namespace Internal
	{
		void PopupDebugErrorMessage(std::string_view title, std::string_view message);
		void PopupSimpleErrorMessage(std::string_view title, std::string_view message);
	}
}

#ifndef GADGET_ASSERT
	#define GADGET_ASSERT(cond, message, ...) { Gadget::Assert((cond), std::format(message, ##__VA_ARGS__), std::source_location::current()); }
#endif // !GADGET_ASSERT

#ifndef GADGET_BASIC_ASSERT
	#define GADGET_BASIC_ASSERT(cond) { Gadget::Assert((cond), #cond); }
#endif // !GADGET_ASSERT_COND
