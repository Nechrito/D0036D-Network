#include "Input.h"

void Input::Update()
{
	std::cout << "Commands" << std::endl;
	std::cout << "1: Randomize" << std::endl;
	std::cout << "2: Set the amount of quads" << std::endl;
	std::cout << ">>";

	int input;
	std::cin >> input;

	std::cerr << "Failed to process your input..." << std::endl;

	switch (input)
	{
		case 1:
			// randomize
			break;
		case 2:
			int amount;
			std::cout << "How many quads?" << std::endl;
			std::cout << ">>";
			std::cin >> amount;
			
			break;
	}
}
