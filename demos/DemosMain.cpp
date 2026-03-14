#include <iostream>
#include <print>

#include "Demo1.hpp"

int main(int argc, char* argv[])
{
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
}
