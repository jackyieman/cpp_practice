#include "pch.h"
#include <iostream>

int main()
{
    std::cout << "Hello World!\n"; 
	std::cout << "Please enter input: ";
	int num{};
	std::cin >> num;
	std::cout << "\nYou entered: " << num;

	return EXIT_SUCCESS;
}
