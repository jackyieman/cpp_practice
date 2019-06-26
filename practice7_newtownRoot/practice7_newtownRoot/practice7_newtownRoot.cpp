#include "pch.h"
#include "NewtownRoot.h"

int main()
{
	NewtownRoot newTest = NewtownRoot(2.0, 3.0, 0.0001);
	newTest.readPolyFromFile("poly.txt");
	newTest.compute();
	newTest.printResult();
	newTest.~NewtownRoot();
}