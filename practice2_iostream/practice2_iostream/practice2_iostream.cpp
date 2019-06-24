#include "pch.h"
#include <iostream>
#include <string>

class Vector {
public:
	//the ':' here means overwrite value in initial
	Vector(int s) :_elem{ new double[s] }, _sz{ s }
	{
	}

	//overload [] operator, so we can use v[i] to take array value
	//return double reference
	double&  operator[](int i)
	{ 
		return _elem[i];
	}
	int size() 
	{
		return _sz;
	}

private:
	double *_elem;
	int _sz;
};

enum class Color{red, blue, green};
enum class TrafficLight { yellow, red, green };

/*
template <typename T>
T minimum(const T &lhs, const T & rhs) {
	return (lhs < rhs) ? lhs : rhs;
}

int get_a(void) {
	return 5;
}

int get_b(void) {
	return 4;
}
*/

double read_and_sum(int s)
{
	Vector v(s); // make a vector of s elements
	for (int i = 0; i < v.size(); ++i) std::cin >> v[i]; // read into elements
	
	double sum = 0;
	for (int i = 0; i < v.size(); ++i) sum += v[i]; // take the sum of the elements
	return sum;
}
TrafficLight& operator++(TrafficLight& t) // prefix increment: ++
{
	switch(t){
		case TrafficLight::green: return t = TrafficLight::yellow;
		case TrafficLight::yellow: return t = TrafficLight::red;
		case TrafficLight::red: return t = TrafficLight::green;
	}
}
int main()
{
	Color col = Color::green;
	TrafficLight light = TrafficLight::yellow;
	TrafficLight next = ++light;
	std::cout << light << "," << next << std::endl;

	std::cout << read_and_sum(5);

	/*
	int x = get_a();
	int b = get_b();
	int i = minimum(x, b);
	std::cout << i << std::endl;
	std::cout << &b << "," << &i << std::endl;
	*/

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