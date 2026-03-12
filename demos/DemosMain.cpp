#include <iostream>
#include <print>

#include "Demo1.hpp"

int main(int argc, char* argv[])
{
	std::println("Pick a Demo: ");
	std::println("[1] Basic Window");

	std::string input;
	std::cin >> input;

	if (input.contains('1'))
	{
		return GadgetCoreDemos::Demo1();
	}

	return 0;
}
