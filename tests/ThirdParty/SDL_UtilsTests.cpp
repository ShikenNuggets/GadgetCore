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
