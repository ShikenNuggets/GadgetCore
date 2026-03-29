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
}
