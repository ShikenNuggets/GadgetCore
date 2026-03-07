#pragma once

#include <array>

namespace Gadget
{
	// DO NOT make any assumptions about the underlying type or numeric values of error codes
	// "OK" will always be 0, errors will always be > 0
	// A future stable version of this library may add additional assurances, but for now I make no promises
	enum class ErrorCode : uint8_t
	{
		OK = 0,
		Unknown,

		// Generic Errors
		InvalidState,
		InvalidArgs,
		FileIO,
		ConstructorFailed,
		OutOfMemory,

		// SDK Errors
		SDL_Error,

		ErrorCode_MAX // TODO - we may not need this in C++26
	};

	// TODO - Replace this with enum to string reflection in C++26
	constexpr std::array<const char*, static_cast<size_t>(ErrorCode::ErrorCode_MAX)> ErrorCodeStr = {
		"OK",
		"Unknown",

		// Generic Errors
		"InvalidState",
		"InvalidArgs",
		"FileIO",
		"ConstructorFailed",
		"OutOfMemory",

		// SDK Errors
		"SDL_Error",

		//ErrorCode_MAX
	};

	constexpr inline const char* GetErrorCodeString(ErrorCode err)
	{
		if (err < ErrorCode::OK || err >= ErrorCode::ErrorCode_MAX)
		{
			return "UnknownErrorCode";
		}

		return ErrorCodeStr.at(static_cast<size_t>(err));
	}
}
