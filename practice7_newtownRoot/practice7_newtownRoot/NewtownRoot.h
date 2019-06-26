#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fstream;

typedef struct _poly {
	double _coef;
	double _power;

	_poly() : _coef{ 0.0 }, _power{ 0 }{}
	_poly(double coef, double power) : _coef{ coef }, _power(power){}
}_POLY;


class NewtownRoot {
private:
	double _result;
	double _x0;
	double _eplison;
	vector<_POLY> _polyList;
	void setPoly(double coef, double power);

public:
	NewtownRoot(double left, double right, double eplison);
	~NewtownRoot();
	void readPolyFromFile(string fileName);
	void compute();
	void printResult() const;
};