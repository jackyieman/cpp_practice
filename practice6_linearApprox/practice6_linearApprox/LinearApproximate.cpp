#include "pch.h"
#include "LinearApproximate.h"

LinearApproximate::LinearApproximate() : _result{ 0 } {}
LinearApproximate::~LinearApproximate() {}

void LinearApproximate::readValueFromFile(string fileName) {
	fstream file;
	file.open(fileName, std::ios::in);

	if (file.is_open()) {
		double value;
		do {
			file >> value;
			_valueList.push_back(value);
		} while (!file.eof());
	}
	else
		cerr << "Error! Cant open the file!\n";
	file.close();
}

void LinearApproximate::compute() {
	//assume f(x) = cube(x)
	//f'(x) = (1/3)* (1/ sqrt(pow(x, 3))
	int x = static_cast<int> (_valueList[0]);
	double fx = cbrt(x);
	double dfx = (1.0 / 3.0) * (1.0 / sqrt(pow((double)x, 3)));
	_result = fx + dfx * (_valueList.at(0) - x);
}

void LinearApproximate::printResult() const {
	cout << _result << endl;
}