#pragma once

#ifdef GADGET_PLATFORM_WINDOWS

#include "Window.hpp"

struct HWND__;
using HWND = HWND__*;

namespace Gadget::Windows_Utils
{
	HWND GetWindowHandle(const Window& window);
}

#endif // GADGET_PLATFORM_WINDOWS
