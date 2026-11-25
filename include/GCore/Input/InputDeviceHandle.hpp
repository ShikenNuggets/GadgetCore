#pragma once

#include <string>

#include <SDL3/SDL.h>

namespace Gadget
{
	class InputDeviceHandle
	{
	public:
		InputDeviceHandle(SDL_JoystickID id);
		~InputDeviceHandle();

		InputDeviceHandle(const InputDeviceHandle&) = delete;
		InputDeviceHandle(InputDeviceHandle&&) = delete;
		InputDeviceHandle& operator=(const InputDeviceHandle&) = delete;
		InputDeviceHandle& operator=(InputDeviceHandle&&) = delete;

		std::string_view GetName() const;
		std::string GetTypeName() const;
		bool IsGamepad() const;

	private:
		SDL_Joystick* joystick;
		SDL_Gamepad* gamepad;
		SDL_JoystickID internalId;
		SDL_JoystickType type;
	};
}
