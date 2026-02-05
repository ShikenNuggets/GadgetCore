#include "Assert.hpp"

#include <array>
#include <filesystem>
#include <format>

#include <SDL3/SDL.h>

#include "Logger.hpp"

using namespace Gadget;

void Gadget::PopupErrorMessage(std::string_view title, std::string_view message)
{
	#ifdef GADGET_BUILD_DEBUG
		Internal::PopupDebugErrorMessage(title, message);
	#else
		Internal::PopupSimpleErrorMessage(title, message);
	#endif 
}

void Gadget::Assert(bool condition, std::string_view message, std::source_location sourceLocation)
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

// TODO - Replace this with std::breakpoint in C++26
#ifndef GADGET_DEBUG_BREAK
	#if defined (_MSC_VER)
		#define GADGET_DEBUG_BREAK() __debugbreak()
	#elif defined (__clang__)
		#define GADGET_DEBUG_BREAK() __builtin_debugtrap()
	#elif defined (__GNUC__) || defined (__GNUG__)
		#define GADGET_DEBUG_BREAK() __builtin_trap()
	#else
		#include <csignal>
		#define GADGET_DEBUG_BREAK() std::raise(SIGTRAP)
	#endif
#endif // !GADGET_DEBUG_BREAK

void Gadget::Internal::PopupDebugErrorMessage(std::string_view title, std::string_view message)
{
	std::array<SDL_MessageBoxButtonData, 3> buttons
	{{
		{ .flags = NULL, .buttonID = 0, .text = "Ignore" },
		{ .flags = NULL, .buttonID = 1, .text = "Break" },
		{ .flags = NULL, .buttonID = 2, .text = "Abort" },
	}};

	SDL_MessageBoxData data{};
	data.flags = SDL_MESSAGEBOX_ERROR;
	data.numbuttons = buttons.size();
	data.buttons = buttons.data();
	data.title = title.data();
	data.message = message.data();

	int buttonId = -1;
	const bool didOpen = SDL_ShowMessageBox(&data, &buttonId);
	if(!didOpen || buttonId < 0 || buttonId > buttons.size())
	{
		Logger::Log(Logger::Error, "Failed to open SDL simple message box. SDL Error: ", SDL_GetError());
		return;
	}

	switch(buttonId)
	{
		case 0:
			return;
		case 1:
			GADGET_DEBUG_BREAK();
			break;
		case 2:
			std::quick_exit(-1);
			break;
	}
}

void Gadget::Internal::PopupSimpleErrorMessage(std::string_view title, std::string_view message)
{
	const bool didOpen = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.data(), message.data(), nullptr);
	if(!didOpen)
	{
		Logger::Log(Logger::Error, "Failed to open SDL simple message box. SDL Error: ", SDL_GetError());
	}
}
