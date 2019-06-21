#include "pch.h"
#include <iostream>
#include <string>

int main()
{
	//std::cout.put('SS');
	//std::cout << "\n" << 3.0;

	//std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	//std::cout.setf 改變stdout的行為
	//std::cout << "\n" << 3.0000;

	//c++ style explict type conversion int('q')
	//std::cout << "\n" << int('q');

	const int a{ 100 };

	//anymous variable
	auto n = 100;
	//n 自動成為 int type;

	char buffer1[10]{ "ABC" };
	char buffer2[10]{};

	//strncpy_s(buffer2, buffer1, 10);
	//memcpy_s(buffer2, 10, buffer1, 2);
	//std::cout << buffer2;
	std::cout << strlen(buffer1);

	//char stringBuffer[10]{};
	//std::cin.getline(stringBuffer, 10, ',');
	//std::cin.getline(targetBuffer, buffer長度[含終止符號], 停止符號)
	//或使用 std::cin.getline(targetBuffer, buffer長度[含終止符號]) 則與std::cin.get效果一樣
	//注意此種方法接收傳統 char buffer 
	//與另一個重載的方法 std::getline 不一樣

	//std::getline 則是接收 string object 和指定的 stream
	//不用煩惱 buffer overflow
	//條件允許下 c++ style 比較適合此方法
	//std::string name;
	//std::getline(std::cin, name);

	//char input[10]{};
	//std::cin.get(input, 10);
	//cin.get(targetBuffer, buffer長度[含終止符號])
	//cin.get不會因為輸入中間有空白停止 , 一直讀到有換行或超過大小
	//cin.get()則立即讀取下一個字符
	//std::cout << input;

	return EXIT_SUCCESS;
}