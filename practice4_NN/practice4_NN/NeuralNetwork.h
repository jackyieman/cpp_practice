#pragma once
#include <vector>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::fstream;

typedef struct nnConfig {
	const int _learnRepeat;
	const double _learnRate;
	const int _inputNodes;
	const int _hiddenNodes;
	const int _outputNodes;

	nnConfig(const int learnRepeat, const double learnRate, const int inputNodes, const int hiddenNodes, const int outputNodes) :
		_learnRepeat(learnRepeat), _learnRate(learnRate), _inputNodes(inputNodes), _hiddenNodes(hiddenNodes), _outputNodes(outputNodes) {}
}NN_CONFIG;

class NeuralNetwork
{
private:
	const NN_CONFIG config;

	clock_t beginTime, endTime;
	double elaspeTime;

	vector< vector<double> > W_xh, W_hy, dW_xh, dW_hy;
	vector<double> X, T, H, Y; //Y is predict data
	vector<double> biasH, biasY, errorH, errorY, dBiasH, dBiasY;
	
	void readFileToBuffer(string fileName, vector<double> &output, int32_t limit);

public:
	NeuralNetwork();
	NeuralNetwork(const NN_CONFIG configRef);
	~NeuralNetwork();

	int learnRepeat() const;
	double learnRate() const;
	int inputNodes() const;
	int hiddenNodes() const;
	int outputNodes() const;

	void initBuffers();
	void setTrainingData(string fileName);
	void setValidData(string fileName);
	void runNN();
	void printResult() const;
};

