// cppPractice0_helloWorld.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

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
