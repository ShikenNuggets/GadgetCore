#ifdef GADGET_PLATFORM_WINDOWS

#include "Platform/Windows/Windows_Utils.hpp"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <SDL3/SDL.h>

using namespace Gadget;

HWND Windows_Utils::GetWindowHandle(const Window& window)
{
	const auto windowProps = SDL_GetWindowProperties(window.GetSDLWindowPtr());
	void* hwndProp = SDL_GetPointerProperty(windowProps, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
	return reinterpret_cast<HWND>(hwndProp); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
}

#endif // GADGET_PLATFORM_WINDOWS
