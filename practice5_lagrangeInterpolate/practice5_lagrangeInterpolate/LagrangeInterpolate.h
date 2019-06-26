#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::fstream;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;

typedef struct _2dPoints {
	double _x;
	double _y;
	_2dPoints() : _x{ 0.0 }, _y{ 0.0 } {}
	_2dPoints(double x, double y) : _x{ x }, _y{ y }{}
} _2DPTS;

class LagrangeInterpolate {
private:
	double _result;
	vector<_2DPTS> _points;

public:
	LagrangeInterpolate();
	~LagrangeInterpolate();
	void setPoints(double x, double y);
	void readPointsFromFile(string fileName);
	void compute(double targetX);
	void printResult(void) const;
};

