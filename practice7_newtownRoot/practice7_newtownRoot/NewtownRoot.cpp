#include "pch.h"
#include "NewtownRoot.h"

NewtownRoot::NewtownRoot(double left, double right, double eplison) : _x0{ (left + right) / 2.0 }, _eplison{ eplison } {}
NewtownRoot::~NewtownRoot() {}

void NewtownRoot::setPoly(double coef, double power) {
	_polyList.push_back(_poly(coef, power));
}

void NewtownRoot::readPolyFromFile(string fileName) {
	fstream file;
	file.open(fileName, std::ios::in);

	if (file.is_open()) {
		do {
			double x; double y;
			file >> x;
			file >> y;
			setPoly(x, y);
			cout << x << "," << y << endl;
		} while (!file.eof());
	}
	else
		cerr << "Read file error! Can't open file.!\n";
	file.close();
}

void NewtownRoot::compute() {
	double x;
	int iter = 0;

	//vector<_POLY> dPolyList;
	//dPolyList.assign(_polyList.begin(), _polyList.end() );
	vector<_POLY> dPolyList(_polyList);  //copy vector by constructor

	for (size_t i = 0; i < dPolyList.size(); i++)
		//if there's constant
		if (dPolyList.at(i)._power <= 0) {
			dPolyList.at(i)._power = 0;
			dPolyList.at(i)._coef = 0;
		}
		else {
			dPolyList.at(i)._coef *= dPolyList.at(i)._power;
			dPolyList.at(i)._power -= 1;
		}

	/*
		Xn+1 = Xn - f(Xn)/f'(Xn)
	*/
	while (iter <= 10000) {
		double fx0 = 0.0;
		double dfx0 = 0.0;
		double offset = 0.0;

		//find f(x0) and f'(x0)
		for (size_t i = 0; i < _polyList.size(); i++) {
			fx0 += _polyList.at(i)._coef * pow(_x0, _polyList.at(i)._power);
			dfx0 += dPolyList.at(i)._coef * pow(_x0, _polyList.at(i)._power);
		}

		if ((fabs(fx0) < _eplison) || ((fabs(dfx0)) < _eplison))
			offset = 0.0;
		else
			offset = fx0 / dfx0;

		x = _x0 - offset;

		if (fabs(x - _x0) < _eplison)
			break;
		iter++;
		_x0 = x;
	}

	_result = _x0;
}

void NewtownRoot::printResult() const{
	cout << _result << endl;
}