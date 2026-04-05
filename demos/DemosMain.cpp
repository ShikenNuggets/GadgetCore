#include <iostream>
#include <print>

#include <SDL3/SDL_main.h>

#include "Demo1.hpp"

int main(int argc, char* argv[])
{
#ifdef GADGET_PLATFORM_TYPE_PC
	std::string input;
	if (argc > 1)
	{
		input = std::span<char*>(argv, argc)[1];
	}

	if (input.empty())
	{
		std::println("Pick a Demo: ");
		std::println("[1] Basic Window");
		std::cin >> input;
	}

	if (input.contains('1'))
	{
		return GadgetCoreDemos::Demo1();
	}
	
	std::println("No valid demo selected, exiting.");
	return 0;
#else
	return GadgetCoreDemos::Demo1(); // TODO - Let the user select the demo with a GUI
#endif //GADGET_PLATFORM_TYPE_PC
}
