// GadgetCore.cpp : Defines the entry point for the application.
//

#include <print>

#include <SDL3/SDL.h>

#include "GCore/GadgetCore.hpp"

#include "GCore/Math/Vector.hpp"

using namespace std;

static constexpr float Pi = 3.141592653589793238f;
static constexpr float NearZero = std::numeric_limits<float>::denorm_min();
static constexpr float Infinity = std::numeric_limits<float>::infinity();

int NotMain()
{
	std::println("{}", SDL_GetVersion());
	

	GCore::TVec2<double> doubleVector;

	cout << "Hello CMake." << endl;
	return 0;
}
