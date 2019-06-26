#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;
using std::fstream;

typedef struct _2dPoints {
	double _x;
	double _y;

	_2dPoints() : _x{ 0.0 }, _y{ 0.0 } {}
	_2dPoints(double x, double y) : _x{ x }, _y{ y }{}
} _2DPTS;

typedef struct _poly {
	double _coef;
	double _power;

	_poly() : _coef{ 0.0 }, _power{ 0 }{}
	_poly(double coef, double power) : _coef{ coef }, _power(power){}
}_POLY;

class LinearApproximate {
private:
	double _result;
	vector<double> _valueList;

public:
	LinearApproximate();
	~LinearApproximate();
	void readValueFromFile(string fileName);
	void compute();
	void printResult() const;
};