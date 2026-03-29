#include "ThirdParty/SDL_Utils.hpp"

#include "Logger.hpp"

using namespace Gadget;

ButtonId SDL_Utils::KeycodeToButtonId(SDL_Keycode key)
{
	switch (key)
	{
		case SDLK_UNKNOWN: return ButtonId::Keyboard_Unknown;
		case SDLK_RETURN: return ButtonId::Keyboard_Return;
		case SDLK_ESCAPE: return ButtonId::Keyboard_Escape;
		case SDLK_BACKSPACE: return ButtonId::Keyboard_Backspace;
		case SDLK_TAB: return ButtonId::Keyboard_Tab;
		case SDLK_SPACE: return ButtonId::Keyboard_Space;
		case SDLK_EXCLAIM: return ButtonId::Keyboard_Exclaim;
		case SDLK_DBLAPOSTROPHE: return ButtonId::Keyboard_DoubleApostrophe;
		case SDLK_HASH: return ButtonId::Keyboard_Hash;
		case SDLK_DOLLAR: return ButtonId::Keyboard_Dollar;
		case SDLK_PERCENT: return ButtonId::Keyboard_Percent;
		case SDLK_AMPERSAND: return ButtonId::Keyboard_Ampersand;
		case SDLK_APOSTROPHE: return ButtonId::Keyboard_Apostrophe;
		case SDLK_LEFTPAREN: return ButtonId::Keyboard_Leftparen;
		case SDLK_RIGHTPAREN: return ButtonId::Keyboard_Rightparen;
		case SDLK_ASTERISK: return ButtonId::Keyboard_Asterisk;
		case SDLK_PLUS: return ButtonId::Keyboard_Plus;
		case SDLK_COMMA: return ButtonId::Keyboard_Comma;
		case SDLK_MINUS: return ButtonId::Keyboard_Minus;
		case SDLK_PERIOD: return ButtonId::Keyboard_Period;
		case SDLK_SLASH: return ButtonId::Keyboard_Slash;

		case SDLK_0: return ButtonId::Keyboard_0;
		case SDLK_1: return ButtonId::Keyboard_1;
		case SDLK_2: return ButtonId::Keyboard_2;
		case SDLK_3: return ButtonId::Keyboard_3;
		case SDLK_4: return ButtonId::Keyboard_4;
		case SDLK_5: return ButtonId::Keyboard_5;
		case SDLK_6: return ButtonId::Keyboard_6;
		case SDLK_7: return ButtonId::Keyboard_7;
		case SDLK_8: return ButtonId::Keyboard_8;
		case SDLK_9: return ButtonId::Keyboard_9;

		case SDLK_COLON: return ButtonId::Keyboard_Colon;
		case SDLK_SEMICOLON: return ButtonId::Keyboard_Semicolon;
		case SDLK_LESS: return ButtonId::Keyboard_Less;
		case SDLK_EQUALS: return ButtonId::Keyboard_Equals;
		case SDLK_GREATER: return ButtonId::Keyboard_Greater;
		case SDLK_QUESTION: return ButtonId::Keyboard_Question;
		case SDLK_AT: return ButtonId::Keyboard_At;
		case SDLK_LEFTBRACKET: return ButtonId::Keyboard_LeftBracket;
		case SDLK_BACKSLASH: return ButtonId::Keyboard_Backslash;
		case SDLK_RIGHTBRACKET: return ButtonId::Keyboard_RightBracket;
		case SDLK_CARET: return ButtonId::Keyboard_Caret;
		case SDLK_UNDERSCORE: return ButtonId::Keyboard_Underscore;
		case SDLK_GRAVE: return ButtonId::Keyboard_Grave;

		case SDLK_A: return ButtonId::Keyboard_A;
		case SDLK_B: return ButtonId::Keyboard_B;
		case SDLK_C: return ButtonId::Keyboard_C;
		case SDLK_D: return ButtonId::Keyboard_D;
		case SDLK_E: return ButtonId::Keyboard_E;
		case SDLK_F: return ButtonId::Keyboard_F;
		case SDLK_G: return ButtonId::Keyboard_G;
		case SDLK_H: return ButtonId::Keyboard_H;
		case SDLK_I: return ButtonId::Keyboard_I;
		case SDLK_J: return ButtonId::Keyboard_J;
		case SDLK_K: return ButtonId::Keyboard_K;
		case SDLK_L: return ButtonId::Keyboard_L;
		case SDLK_M: return ButtonId::Keyboard_M;
		case SDLK_N: return ButtonId::Keyboard_N;
		case SDLK_O: return ButtonId::Keyboard_O;
		case SDLK_P: return ButtonId::Keyboard_P;
		case SDLK_Q: return ButtonId::Keyboard_Q;
		case SDLK_R: return ButtonId::Keyboard_R;
		case SDLK_S: return ButtonId::Keyboard_S;
		case SDLK_T: return ButtonId::Keyboard_T;
		case SDLK_U: return ButtonId::Keyboard_U;
		case SDLK_V: return ButtonId::Keyboard_V;
		case SDLK_W: return ButtonId::Keyboard_W;
		case SDLK_X: return ButtonId::Keyboard_X;
		case SDLK_Y: return ButtonId::Keyboard_Y;
		case SDLK_Z: return ButtonId::Keyboard_Z;

		case SDLK_LEFTBRACE: return ButtonId::Keyboard_LeftBrace;
		case SDLK_PIPE: return ButtonId::Keyboard_Pipe;
		case SDLK_RIGHTBRACE: return ButtonId::Keyboard_RightBrace;
		case SDLK_TILDE: return ButtonId::Keyboard_Tilde;
		case SDLK_DELETE: return ButtonId::Keyboard_Delete;
		case SDLK_PLUSMINUS: return ButtonId::Keyboard_PlusMinus;

		case SDLK_CAPSLOCK: return ButtonId::Keyboard_CapsLock;
		case SDLK_F1: return ButtonId::Keyboard_F1;
		case SDLK_F2: return ButtonId::Keyboard_F2;
		case SDLK_F3: return ButtonId::Keyboard_F3;
		case SDLK_F4: return ButtonId::Keyboard_F4;
		case SDLK_F5: return ButtonId::Keyboard_F5;
		case SDLK_F6: return ButtonId::Keyboard_F6;
		case SDLK_F7: return ButtonId::Keyboard_F7;
		case SDLK_F8: return ButtonId::Keyboard_F8;
		case SDLK_F9: return ButtonId::Keyboard_F9;
		case SDLK_F10: return ButtonId::Keyboard_F10;
		case SDLK_F11: return ButtonId::Keyboard_F11;
		case SDLK_F12: return ButtonId::Keyboard_F12;
		case SDLK_PRINTSCREEN: return ButtonId::Keyboard_PrintScreen;
		case SDLK_SCROLLLOCK: return ButtonId::Keyboard_ScrollLock;
		case SDLK_PAUSE: return ButtonId::Keyboard_Pause;
		case SDLK_INSERT: return ButtonId::Keyboard_Insert;
		case SDLK_HOME: return ButtonId::Keyboard_Home;
		case SDLK_PAGEUP: return ButtonId::Keyboard_PageUp;
		case SDLK_END: return ButtonId::Keyboard_End;
		case SDLK_PAGEDOWN: return ButtonId::Keyboard_PageDown;
		case SDLK_RIGHT: return ButtonId::Keyboard_Right;
		case SDLK_LEFT: return ButtonId::Keyboard_Left;
		case SDLK_DOWN: return ButtonId::Keyboard_Down;
		case SDLK_UP: return ButtonId::Keyboard_Up;
		case SDLK_NUMLOCKCLEAR: return ButtonId::Keyboard_NumLockClear;

		case SDLK_KP_DIVIDE: return ButtonId::Keyboard_KP_Divide;
		case SDLK_KP_MULTIPLY: return ButtonId::Keyboard_KP_Multiply;
		case SDLK_KP_MINUS: return ButtonId::Keyboard_KP_Minus;
		case SDLK_KP_PLUS: return ButtonId::Keyboard_KP_Plus;
		case SDLK_KP_ENTER: return ButtonId::Keyboard_KP_Enter;
		case SDLK_KP_1: return ButtonId::Keyboard_KP_1;
		case SDLK_KP_2: return ButtonId::Keyboard_KP_2;
		case SDLK_KP_3: return ButtonId::Keyboard_KP_3;
		case SDLK_KP_4: return ButtonId::Keyboard_KP_4;
		case SDLK_KP_5: return ButtonId::Keyboard_KP_5;
		case SDLK_KP_6: return ButtonId::Keyboard_KP_6;
		case SDLK_KP_7: return ButtonId::Keyboard_KP_7;
		case SDLK_KP_8: return ButtonId::Keyboard_KP_8;
		case SDLK_KP_9: return ButtonId::Keyboard_KP_9;
		case SDLK_KP_0: return ButtonId::Keyboard_KP_0;
		case SDLK_KP_PERIOD: return ButtonId::Keyboard_KP_Period;

		case SDLK_APPLICATION: return ButtonId::Keyboard_Application;
		case SDLK_POWER: return ButtonId::Keyboard_Power;
		case SDLK_KP_EQUALS: return ButtonId::Keyboard_KP_Equals;
		case SDLK_F13: return ButtonId::Keyboard_F13;
		case SDLK_F14: return ButtonId::Keyboard_F14;
		case SDLK_F15: return ButtonId::Keyboard_F15;
		case SDLK_F16: return ButtonId::Keyboard_F16;
		case SDLK_F17: return ButtonId::Keyboard_F17;
		case SDLK_F18: return ButtonId::Keyboard_F18;
		case SDLK_F19: return ButtonId::Keyboard_F19;
		case SDLK_F20: return ButtonId::Keyboard_F20;
		case SDLK_F21: return ButtonId::Keyboard_F21;
		case SDLK_F22: return ButtonId::Keyboard_F22;
		case SDLK_F23: return ButtonId::Keyboard_F23;
		case SDLK_F24: return ButtonId::Keyboard_F24;
		case SDLK_EXECUTE: return ButtonId::Keyboard_Execute;
		case SDLK_HELP: return ButtonId::Keyboard_Help;
		case SDLK_MENU: return ButtonId::Keyboard_Menu;
		case SDLK_SELECT: return ButtonId::Keyboard_Select;
		case SDLK_STOP: return ButtonId::Keyboard_Stop;
		case SDLK_AGAIN: return ButtonId::Keyboard_Again;
		case SDLK_UNDO: return ButtonId::Keyboard_Undo;
		case SDLK_CUT: return ButtonId::Keyboard_Cut;
		case SDLK_COPY: return ButtonId::Keyboard_Copy;
		case SDLK_PASTE: return ButtonId::Keyboard_Paste;
		case SDLK_FIND: return ButtonId::Keyboard_Find;
		case SDLK_MUTE: return ButtonId::Keyboard_Mute;
		case SDLK_VOLUMEUP: return ButtonId::Keyboard_VolumeUp;
		case SDLK_VOLUMEDOWN: return ButtonId::Keyboard_VolumeDown;

		case SDLK_KP_COMMA: return ButtonId::Keyboard_KP_Comma;
		case SDLK_KP_EQUALSAS400: return ButtonId::Keyboard_KP_EqualsAS400;
		case SDLK_ALTERASE: return ButtonId::Keyboard_AltErase;
		case SDLK_SYSREQ: return ButtonId::Keyboard_SysReq;
		case SDLK_CANCEL: return ButtonId::Keyboard_Cancel;
		case SDLK_CLEAR: return ButtonId::Keyboard_Clear;
		case SDLK_PRIOR: return ButtonId::Keyboard_Prior;
		case SDLK_RETURN2: return ButtonId::Keyboard_Return2;
		case SDLK_SEPARATOR: return ButtonId::Keyboard_Separator;
		case SDLK_OUT: return ButtonId::Keyboard_Out;
		case SDLK_OPER: return ButtonId::Keyboard_Oper;
		case SDLK_CLEARAGAIN: return ButtonId::Keyboard_ClearAgain;
		case SDLK_CRSEL: return ButtonId::Keyboard_CrSel;
		case SDLK_EXSEL: return ButtonId::Keyboard_ExSel;
		case SDLK_KP_00: return ButtonId::Keyboard_KP_00;
		case SDLK_KP_000: return ButtonId::Keyboard_KP_000;
		case SDLK_THOUSANDSSEPARATOR: return ButtonId::Keyboard_ThousandsSeparator;
		case SDLK_DECIMALSEPARATOR: return ButtonId::Keyboard_DecimalSeparator;
		case SDLK_CURRENCYUNIT: return ButtonId::Keyboard_CurrencyUnit;
		case SDLK_CURRENCYSUBUNIT: return ButtonId::Keyboard_CurrencySubunit;
		case SDLK_KP_LEFTPAREN: return ButtonId::Keyboard_KP_LeftParen;
		case SDLK_KP_RIGHTPAREN: return ButtonId::Keyboard_KP_RightParen;
		case SDLK_KP_LEFTBRACE: return ButtonId::Keyboard_KP_LeftBrace;
		case SDLK_KP_RIGHTBRACE: return ButtonId::Keyboard_KP_RightBrace;
		case SDLK_KP_TAB: return ButtonId::Keyboard_KP_Tab;
		case SDLK_KP_BACKSPACE: return ButtonId::Keyboard_KP_Backspace;
		case SDLK_KP_A: return ButtonId::Keyboard_KP_A;
		case SDLK_KP_B: return ButtonId::Keyboard_KP_B;
		case SDLK_KP_C: return ButtonId::Keyboard_KP_C;
		case SDLK_KP_D: return ButtonId::Keyboard_KP_D;
		case SDLK_KP_E: return ButtonId::Keyboard_KP_E;
		case SDLK_KP_F: return ButtonId::Keyboard_KP_F;
		case SDLK_KP_XOR: return ButtonId::Keyboard_KP_XOR;
		case SDLK_KP_POWER: return ButtonId::Keyboard_KP_Power;
		case SDLK_KP_PERCENT: return ButtonId::Keyboard_KP_Percent;
		case SDLK_KP_LESS: return ButtonId::Keyboard_KP_Less;
		case SDLK_KP_GREATER: return ButtonId::Keyboard_KP_Greater;
		case SDLK_KP_AMPERSAND: return ButtonId::Keyboard_KP_Ampersand;
		case SDLK_KP_DBLAMPERSAND: return ButtonId::Keyboard_KP_DoubleAmpersand;
		case SDLK_KP_VERTICALBAR: return ButtonId::Keyboard_KP_VerticalBar;
		case SDLK_KP_DBLVERTICALBAR: return ButtonId::Keyboard_KP_DoubleVerticalBar;
		case SDLK_KP_COLON: return ButtonId::Keyboard_KP_Colon;
		case SDLK_KP_HASH: return ButtonId::Keyboard_KP_Hash;
		case SDLK_KP_SPACE: return ButtonId::Keyboard_KP_Space;
		case SDLK_KP_AT: return ButtonId::Keyboard_KP_At;
		case SDLK_KP_EXCLAM: return ButtonId::Keyboard_KP_Exclam;
		case SDLK_KP_MEMSTORE: return ButtonId::Keyboard_KP_MemStore;
		case SDLK_KP_MEMRECALL: return ButtonId::Keyboard_KP_MemRecall;
		case SDLK_KP_MEMCLEAR: return ButtonId::Keyboard_KP_MemClear;
		case SDLK_KP_MEMADD: return ButtonId::Keyboard_KP_MemAdd;
		case SDLK_KP_MEMSUBTRACT: return ButtonId::Keyboard_KP_MemSubtract;
		case SDLK_KP_MEMMULTIPLY: return ButtonId::Keyboard_KP_MemMultiply;
		case SDLK_KP_MEMDIVIDE: return ButtonId::Keyboard_KP_MemDivide;
		case SDLK_KP_PLUSMINUS: return ButtonId::Keyboard_KP_PlusMinus;
		case SDLK_KP_CLEAR: return ButtonId::Keyboard_KP_Clear;
		case SDLK_KP_CLEARENTRY: return ButtonId::Keyboard_KP_ClearEntry;
		case SDLK_KP_BINARY: return ButtonId::Keyboard_KP_Binary;
		case SDLK_KP_OCTAL: return ButtonId::Keyboard_KP_Octal;
		case SDLK_KP_DECIMAL: return ButtonId::Keyboard_KP_Decimal;
		case SDLK_KP_HEXADECIMAL: return ButtonId::Keyboard_KP_Hexadecimal;

		case SDLK_LCTRL: return ButtonId::Keyboard_LeftCtrl;
		case SDLK_LSHIFT: return ButtonId::Keyboard_LeftShift;
		case SDLK_LALT: return ButtonId::Keyboard_LeftAlt;
		case SDLK_LGUI: return ButtonId::Keyboard_LeftGUI;
		case SDLK_RCTRL: return ButtonId::Keyboard_RightCtrl;
		case SDLK_RSHIFT: return ButtonId::Keyboard_RightShift;
		case SDLK_RALT: return ButtonId::Keyboard_RightAlt;
		case SDLK_RGUI: return ButtonId::Keyboard_RightGUI;
		case SDLK_MODE: return ButtonId::Keyboard_Mode;

		case SDLK_SLEEP: return ButtonId::Keyboard_Sleep;
		case SDLK_WAKE: return ButtonId::Keyboard_Wake;
		case SDLK_CHANNEL_INCREMENT: return ButtonId::Keyboard_Channel_Increment;
		case SDLK_CHANNEL_DECREMENT: return ButtonId::Keyboard_Channel_Decrement;
		case SDLK_MEDIA_PLAY: return ButtonId::Keyboard_Media_Play;
		case SDLK_MEDIA_PAUSE: return ButtonId::Keyboard_Media_Pause;
		case SDLK_MEDIA_RECORD: return ButtonId::Keyboard_Media_Record;
		case SDLK_MEDIA_FAST_FORWARD: return ButtonId::Keyboard_Media_FastForward;
		case SDLK_MEDIA_REWIND: return ButtonId::Keyboard_Media_Rewind;
		case SDLK_MEDIA_NEXT_TRACK: return ButtonId::Keyboard_Media_NextTrack;
		case SDLK_MEDIA_PREVIOUS_TRACK: return ButtonId::Keyboard_Media_PreviousTrack;
		case SDLK_MEDIA_STOP: return ButtonId::Keyboard_Media_Stop;
		case SDLK_MEDIA_EJECT: return ButtonId::Keyboard_Media_Eject;
		case SDLK_MEDIA_PLAY_PAUSE: return ButtonId::Keyboard_Media_Play_Pause;
		case SDLK_MEDIA_SELECT: return ButtonId::Keyboard_Media_Select;

		case SDLK_AC_NEW: return ButtonId::Keyboard_AC_New;
		case SDLK_AC_OPEN: return ButtonId::Keyboard_AC_Open;
		case SDLK_AC_CLOSE: return ButtonId::Keyboard_AC_Close;
		case SDLK_AC_EXIT: return ButtonId::Keyboard_AC_Exit;
		case SDLK_AC_SAVE: return ButtonId::Keyboard_AC_Save;
		case SDLK_AC_PRINT: return ButtonId::Keyboard_AC_Print;
		case SDLK_AC_PROPERTIES: return ButtonId::Keyboard_AC_Properties;
		case SDLK_AC_SEARCH: return ButtonId::Keyboard_AC_Search;
		case SDLK_AC_HOME: return ButtonId::Keyboard_AC_Home;
		case SDLK_AC_BACK: return ButtonId::Keyboard_AC_Back;
		case SDLK_AC_FORWARD: return ButtonId::Keyboard_AC_Forward;
		case SDLK_AC_STOP: return ButtonId::Keyboard_AC_Stop;
		case SDLK_AC_REFRESH: return ButtonId::Keyboard_AC_Refresh;
		case SDLK_AC_BOOKMARKS: return ButtonId::Keyboard_AC_Bookmarks;

		case SDLK_SOFTLEFT: return ButtonId::Keyboard_SoftLeft;
		case SDLK_SOFTRIGHT: return ButtonId::Keyboard_SoftRight;
		case SDLK_CALL: return ButtonId::Keyboard_Call;
		case SDLK_ENDCALL: return ButtonId::Keyboard_Endcall;
		case SDLK_LEFT_TAB: return ButtonId::Keyboard_LeftTab;
		case SDLK_LEVEL5_SHIFT: return ButtonId::Keyboard_Level5_Shift;
		case SDLK_MULTI_KEY_COMPOSE: return ButtonId::Keyboard_Multi_Key_Compose;
		case SDLK_LMETA: return ButtonId::Keyboard_LeftMeta;
		case SDLK_RMETA: return ButtonId::Keyboard_RightMeta;
		case SDLK_LHYPER: return ButtonId::Keyboard_LeftHyper;
		case SDLK_RHYPER: return ButtonId::Keyboard_RightHyper;

		default: break;
	}

	GADGET_LOG_WARNING("Cannot process unrecognized SDL keycode: {}", key);
	return ButtonId::None;
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

AxisId SDL_Utils::GamepadToAxisId(Uint8 axis)
{
	switch (axis)
	{
		case SDL_GAMEPAD_AXIS_LEFTX:
			return AxisId::Gamepad_LeftStick_Horizontal;
		case SDL_GAMEPAD_AXIS_LEFTY:
			return AxisId::Gamepad_LeftStick_Vertical;
		case SDL_GAMEPAD_AXIS_RIGHTX:
			return AxisId::Gamepad_RightStick_Horizontal;
		case SDL_GAMEPAD_AXIS_RIGHTY:
			return AxisId::Gamepad_RightStick_Vertical;
		case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
			return AxisId::Gamepad_LeftTrigger;
		case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
			return AxisId::Gamepad_RightTrigger;
		default:
			GADGET_LOG_ERROR("Unsupported SDL gamepad axis: {}", axis);
			break;
	}

	return AxisId::None;
}

ButtonId SDL_Utils::GamepadtoButtonId(Uint8 button)
{
	switch (button)
	{
		case SDL_GAMEPAD_BUTTON_SOUTH:
			return ButtonId::Gamepad_Face_Down;
		case SDL_GAMEPAD_BUTTON_EAST:
			return ButtonId::Gamepad_Face_Right;
		case SDL_GAMEPAD_BUTTON_WEST:
			return ButtonId::Gamepad_Face_Left;
		case SDL_GAMEPAD_BUTTON_NORTH:
			return ButtonId::Gamepad_Face_Up;
		case SDL_GAMEPAD_BUTTON_BACK:
			return ButtonId::Gamepad_Select;
		case SDL_GAMEPAD_BUTTON_GUIDE:
			return ButtonId::Gamepad_Home;
		case SDL_GAMEPAD_BUTTON_START:
			return ButtonId::Gamepad_Start;
		case SDL_GAMEPAD_BUTTON_LEFT_STICK:
			return ButtonId::Gamepad_AnalogClick_Left;
		case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
			return ButtonId::Gamepad_AnalogClick_Right;
		case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
			return ButtonId::Gamepad_Shoulder_L1;
		case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
			return ButtonId::Gamepad_Shoulder_R1;
		case SDL_GAMEPAD_BUTTON_DPAD_UP:
			return ButtonId::Gamepad_Dpad_Up;
		case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
			return ButtonId::Gamepad_Dpad_Down;
		case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
			return ButtonId::Gamepad_Dpad_Left;
		case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
			return ButtonId::Gamepad_Dpad_Right;
		case SDL_GAMEPAD_BUTTON_MISC1:
			return ButtonId::Gamepad_Misc1;
		case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1:
			return ButtonId::Gamepad_Paddle_Right1;
		case SDL_GAMEPAD_BUTTON_LEFT_PADDLE1:
			return ButtonId::Gamepad_Paddle_Left1;
		case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2:
			return ButtonId::Gamepad_Paddle_Right2;
		case SDL_GAMEPAD_BUTTON_LEFT_PADDLE2:
			return ButtonId::Gamepad_Paddle_Left2;
		case SDL_GAMEPAD_BUTTON_TOUCHPAD:
			return ButtonId::Gamepad_Touchpad;
		case SDL_GAMEPAD_BUTTON_MISC2:
			return ButtonId::Gamepad_Misc2;
		case SDL_GAMEPAD_BUTTON_MISC3:
			return ButtonId::Gamepad_Misc3;
		case SDL_GAMEPAD_BUTTON_MISC4:
			return ButtonId::Gamepad_Misc4;
		case SDL_GAMEPAD_BUTTON_MISC5:
			return ButtonId::Gamepad_Misc5;
		case SDL_GAMEPAD_BUTTON_MISC6:
			return ButtonId::Gamepad_Misc6;
	}

	return ButtonId::None;
}
