#include "pch.h"
#include "LagrangeInterpolate.h"

int main()
{
	LagrangeInterpolate newTest = LagrangeInterpolate();
	newTest.readPointsFromFile("points.txt");
	newTest.compute(1.5);
	newTest.printResult();
	newTest.~LagrangeInterpolate();
}
