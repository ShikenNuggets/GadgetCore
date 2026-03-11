#include "ThirdParty/SDL_Utils.hpp"

#include "Logger.hpp"

using namespace Gadget;

ButtonId SDL_Utils::KeycodeToButtonId(SDL_Keycode key)
{
	const auto buttonIdx = static_cast<uint16_t>(ButtonId::Keyboard_Unknown) + static_cast<uint16_t>(key);
	const auto buttonId = static_cast<ButtonId>(buttonIdx);

	if (buttonId < ButtonId::Keyboard_Unknown || buttonId >= ButtonId::ButtonId_MAX)
	{
		GADGET_LOG_ERROR("Unsupported SDL keycode: {}", key);
		return ButtonId::None;
	}

	return buttonId;
}

ButtonId SDL_Utils::MouseToButtonId(Uint8 button)
{
	switch (button)
	{
		case SDL_BUTTON_LEFT:
			return ButtonId::Mouse_Left;
		case SDL_BUTTON_RIGHT:
			return ButtonId::Mouse_Right;
		case SDL_BUTTON_MIDDLE:
			return ButtonId::Mouse_Middle;
		case SDL_BUTTON_X1:
			return ButtonId::Mouse_Button_4;
		case SDL_BUTTON_X2:
			return ButtonId::Mouse_Button_5;
		default:
			GADGET_LOG_ERROR("Unsupported SDL mouse button: {}", button);
			break;
	}

	return ButtonId::None;
}
