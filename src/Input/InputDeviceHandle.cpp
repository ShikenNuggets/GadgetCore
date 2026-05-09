#include "Input/InputDeviceHandle.hpp"

#include "Assert.hpp"
#include "Logger.hpp"

using namespace Gadget;

InputDeviceHandle::InputDeviceHandle(SDL_JoystickID id) : internalId(id), joystick(SDL_OpenJoystick(id)), gamepad(nullptr), type(SDL_JOYSTICK_TYPE_UNKNOWN)
{
	if (joystick == nullptr)
	{
		GADGET_LOG_ERROR("Failed to open joystick ID {}! SDL Error: {}", internalId, SDL_GetError());
		return; // TODO - throw?
	}

	type = SDL_GetJoystickType(joystick);
	GADGET_LOG_INFO("Connected {} ({}) with ID {}", GetName(), GetTypeName(), internalId);

	if (type == SDL_JOYSTICK_TYPE_GAMEPAD)
	{
		gamepad = SDL_OpenGamepad(internalId);
		if (gamepad == nullptr)
		{
			GADGET_LOG_ERROR("Failed to open gamepad for joystick ID {}! SDL Error: {}", internalId, SDL_GetError());
		}
	}
}

InputDeviceHandle::~InputDeviceHandle()
{
	if (gamepad != nullptr)
	{
		SDL_CloseGamepad(gamepad);
	}

	if (joystick != nullptr)
	{
		SDL_CloseJoystick(joystick);
	}
}

std::string_view InputDeviceHandle::GetName() const
{
	return SDL_GetJoystickName(joystick);
}

std::string InputDeviceHandle::GetTypeName() const
{
	switch (type)
	{
		case SDL_JOYSTICK_TYPE_UNKNOWN:
			return "Unknown";
		case SDL_JOYSTICK_TYPE_GAMEPAD:
			return "Gamepad";
		case SDL_JOYSTICK_TYPE_WHEEL:
			return "Wheel";
		case SDL_JOYSTICK_TYPE_ARCADE_STICK:
			return "Arcade Stick";
		case SDL_JOYSTICK_TYPE_FLIGHT_STICK:
			return "Flight Stick";
		case SDL_JOYSTICK_TYPE_DANCE_PAD:
			return "Dance Pad";
		case SDL_JOYSTICK_TYPE_GUITAR:
			return "Guitar";
		case SDL_JOYSTICK_TYPE_DRUM_KIT:
			return "Drum Kit";
		case SDL_JOYSTICK_TYPE_ARCADE_PAD:
			return "Arcade Pad";
		case SDL_JOYSTICK_TYPE_THROTTLE:
			return "Throttle";
		default:
			break;
	}

	return std::format("{}", std::to_underlying(type));
}

bool InputDeviceHandle::IsGamepad() const
{
	return type == SDL_JOYSTICK_TYPE_GAMEPAD && gamepad != nullptr;
}
