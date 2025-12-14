#pragma once

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
		SDL_Error
	};
}
