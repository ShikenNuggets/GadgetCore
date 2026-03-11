#pragma once

#include <cstdint>

#include "Delegate.hpp"
#include "Input/InputDefines.hpp"

namespace Gadget
{
	using QuitDelegateT = Delegate<void(void)>;

	using WindowSizeDelegateT = Delegate<void(int32_t, int32_t)>; // Parameters: New window size (w, h)
	using WindowPosDelegateT = Delegate<void(int32_t, int32_t)>; // Parameters: New window position (x, y)

	using ButtonDelegateT = Delegate<void(ButtonId)>;
	using AxisChangeDelegateT = Delegate<void(AxisId, double)>;

	struct WindowEventHandler
	{
		// App Events
		QuitDelegateT OnQuitRequested;

		// Window Events
		WindowSizeDelegateT OnWindowResized;
		WindowPosDelegateT OnWindowMoved;

		// Key Events
		ButtonDelegateT OnButtonDown;
		ButtonDelegateT OnButtonUp;
		AxisChangeDelegateT OnAxisChange;
	};
}
