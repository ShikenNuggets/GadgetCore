#pragma once

#include <SDL3/SDL.h>

#include "GCore/Input/InputDefines.hpp"

namespace Gadget::SDL_Utils
{
	ButtonId KeycodeToButtonId(SDL_Keycode key);
	ButtonId MouseToButtonId(Uint8 button);
	AxisId GamepadToAxisId(Uint8 axis);
	ButtonId GamepadtoButtonId(Uint8 button);
}
