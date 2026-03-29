#include <catch2/catch_all.hpp>

#include <GCore/ThirdParty/SDL_Utils.hpp>

using namespace Gadget;

TEST_CASE("SDL_Utils::KeycodeToButtonId", "[sdl_utils_keycode_to_button_id]")
{
	REQUIRE(SDL_Utils::KeycodeToButtonId(SDLK_A) == ButtonId::Keyboard_A);
	REQUIRE(SDL_Utils::KeycodeToButtonId(SDLK_Z) == ButtonId::Keyboard_Z);

	REQUIRE(SDL_Utils::KeycodeToButtonId(SDLK_0) == ButtonId::Keyboard_0);
	REQUIRE(SDL_Utils::KeycodeToButtonId(SDLK_9) == ButtonId::Keyboard_9);

	REQUIRE(SDL_Utils::KeycodeToButtonId(SDLK_F1) == ButtonId::Keyboard_F1);
	REQUIRE(SDL_Utils::KeycodeToButtonId(SDLK_F12) == ButtonId::Keyboard_F12);
}

TEST_CASE("SDL_Utils::MouseToButtonId", "[sdl_utils_mouse_to_button_id]")
{
	REQUIRE(SDL_Utils::MouseToButtonId(SDL_BUTTON_LEFT) == ButtonId::Mouse_Left);
	REQUIRE(SDL_Utils::MouseToButtonId(SDL_BUTTON_MIDDLE) == ButtonId::Mouse_Middle);
	REQUIRE(SDL_Utils::MouseToButtonId(SDL_BUTTON_RIGHT) == ButtonId::Mouse_Right);
	REQUIRE(SDL_Utils::MouseToButtonId(SDL_BUTTON_X1) == ButtonId::Mouse_Button_4);
	REQUIRE(SDL_Utils::MouseToButtonId(SDL_BUTTON_X2) == ButtonId::Mouse_Button_5);
}

TEST_CASE("SDL_Utils::GamepadToAxisId", "[sdl_utils_gamepad_to_axis_id]")
{
	REQUIRE(SDL_Utils::GamepadToAxisId(SDL_GAMEPAD_AXIS_LEFTX) == AxisId::Gamepad_LeftStick_Horizontal);
	REQUIRE(SDL_Utils::GamepadToAxisId(SDL_GAMEPAD_AXIS_LEFTY) == AxisId::Gamepad_LeftStick_Vertical);
	REQUIRE(SDL_Utils::GamepadToAxisId(SDL_GAMEPAD_AXIS_RIGHTX) == AxisId::Gamepad_RightStick_Horizontal);
	REQUIRE(SDL_Utils::GamepadToAxisId(SDL_GAMEPAD_AXIS_RIGHTY) == AxisId::Gamepad_RightStick_Vertical);
	REQUIRE(SDL_Utils::GamepadToAxisId(SDL_GAMEPAD_AXIS_LEFT_TRIGGER) == AxisId::Gamepad_LeftTrigger);
	REQUIRE(SDL_Utils::GamepadToAxisId(SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) == AxisId::Gamepad_RightTrigger);

	REQUIRE(SDL_Utils::GamepadToAxisId(SDL_GAMEPAD_AXIS_INVALID) == AxisId::None);
}

TEST_CASE("SDL_Utils::GamepadToButtonId", "[sdl_utils_gamepad_to_button_id]")
{
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_SOUTH) == ButtonId::Gamepad_Face_Down);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_EAST) == ButtonId::Gamepad_Face_Right);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_WEST) == ButtonId::Gamepad_Face_Left);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_NORTH) == ButtonId::Gamepad_Face_Up);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_BACK) == ButtonId::Gamepad_Select);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_GUIDE) == ButtonId::Gamepad_Home);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_START) == ButtonId::Gamepad_Start);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_LEFT_STICK) == ButtonId::Gamepad_AnalogClick_Left);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_RIGHT_STICK) == ButtonId::Gamepad_AnalogClick_Right);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_LEFT_SHOULDER) == ButtonId::Gamepad_Shoulder_L1);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER) == ButtonId::Gamepad_Shoulder_R1);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_DPAD_UP) == ButtonId::Gamepad_Dpad_Up);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_DPAD_DOWN) == ButtonId::Gamepad_Dpad_Down);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_DPAD_LEFT) == ButtonId::Gamepad_Dpad_Left);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_DPAD_RIGHT) == ButtonId::Gamepad_Dpad_Right);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_MISC1) == ButtonId::Gamepad_Misc1);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1) == ButtonId::Gamepad_Paddle_Right1);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_LEFT_PADDLE1) == ButtonId::Gamepad_Paddle_Left1);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2) == ButtonId::Gamepad_Paddle_Right2);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_LEFT_PADDLE2) == ButtonId::Gamepad_Paddle_Left2);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_TOUCHPAD) == ButtonId::Gamepad_Touchpad);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_MISC2) == ButtonId::Gamepad_Misc2);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_MISC3) == ButtonId::Gamepad_Misc3);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_MISC4) == ButtonId::Gamepad_Misc4);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_MISC5) == ButtonId::Gamepad_Misc5);
	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_MISC6) == ButtonId::Gamepad_Misc6);

	REQUIRE(SDL_Utils::GamepadtoButtonId(SDL_GAMEPAD_BUTTON_INVALID) == ButtonId::None);
}
