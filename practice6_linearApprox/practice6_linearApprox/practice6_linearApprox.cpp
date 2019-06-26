#include "pch.h"
#include "LinearApproximate.h"

int main()
{
	LinearApproximate newTest = LinearApproximate();
	newTest.readValueFromFile("value.txt");
	newTest.compute();
	newTest.printResult();
	newTest.~LinearApproximate();
}

