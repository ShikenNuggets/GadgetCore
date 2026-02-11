#pragma once

#include <cstdint>

#include "Delegate.hpp"

namespace Gadget
{
	using QuitDelegateT = Delegate<void(void)>;

	using WindowResizedDelegateT = Delegate<void(int32_t, int32_t)>; // Parameters: New window size (w, h)
	using WindowMovedDelegateT = Delegate<void(int32_t, int32_t)>; // Parameters: New window position (x, y)

	using KeyDownDelegateT = Delegate<void(void)>;
	using KeyUpDelegateT = Delegate<void(void)>;

	struct WindowEventHandler
	{
		// App Events
		Delegate<void(void)> OnQuitRequested;

		// Window Events
		Delegate<void(int32_t, int32_t)> OnWindowResized;
		Delegate<void(int32_t, int32_t)> OnWindowMoved;

		// Key Events
		Delegate<void(void)> OnKeyDown;
		Delegate<void(void)> OnKeyUp;
	};
}
