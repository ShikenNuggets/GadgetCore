#pragma once

#include <SDL3/SDL.h>

#include "Input/InputDefines.hpp"

namespace Gadget::SDL_Utils
{
	ButtonId KeycodeToButtonId(SDL_Keycode key);
	ButtonId MouseToButtonId(Uint8 button);
}
