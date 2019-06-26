#include "pch.h"
#include "LagrangeInterpolate.h"

LagrangeInterpolate::LagrangeInterpolate() : _result(0.0) {}
LagrangeInterpolate::~LagrangeInterpolate() {}

void LagrangeInterpolate::setPoints(double x, double y) {
	_points.push_back(_2dPoints(x, y));
}

void LagrangeInterpolate::readPointsFromFile(string fileName) {
	fstream file;
	file.open(fileName, std::ios::in);

	if (file.is_open()) {
		do {
			double x, y;
			file >> x;
			file >> y;
			setPoints(x, y);
		} while (!file.eof());
	}
	else
		cerr << "Read file error! Can't open file.!\n";
	file.close();
}

void LagrangeInterpolate::compute(double targetX) {
	double resultY = 0.0;
	for (size_t i = 0; i < _points.size(); i++) {
		double upper = 1.0;
		double lower = 1.0;
		for (size_t j = 0; j < _points.size(); j++) {
			if (j == i) continue;
			upper *= (targetX - _points[j]._x);
			lower *= _points.at(i)._x - _points.at(j)._x;
		}
		resultY += (upper / lower) * _points[i]._y;
	}
	_result = resultY;
}

void LagrangeInterpolate::printResult() const {
	cout << _result << endl;
}