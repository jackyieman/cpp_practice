#include "pch.h"
#include <iostream>
#include <vector>
#include <ctime>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

typedef struct nnConfig{
	const int _learnRepeat;
	const double _learnRate;
	const int _inputNodes;
	const int _hiddenNodes;
	const int _outputNodes;

	nnConfig(int learnRepeat, double learnRate, int inputNodes, int hiddenNodes, int outputNodes) : 
		_learnRepeat(learnRepeat), _learnRate(learnRate), _inputNodes(inputNodes), _hiddenNodes(hiddenNodes), _outputNodes(outputNodes) {}
}NN_CONFIG;

class NeuralNetwork {
private:
	const NN_CONFIG config;

	clock_t beginTime, endTime;
	double elaspeTime;

	vector< vector<double> > W_xh, W_hy, dW_xh, dW_hy;
	vector<double> X, T, H, Y; //Y is predict data
	vector<double> biasH, biasY, errorH, errorY, dBiasH, dBiasY;
 
public:
	NeuralNetwork() :config(500, 0.05, 25, 5, 5) {}
	NeuralNetwork(const NN_CONFIG configRef) : config(configRef._learnRepeat, configRef._learnRate, configRef._inputNodes, configRef._hiddenNodes, configRef._outputNodes) {}
	~NeuralNetwork() { }

	int learnRepeat() { return config._learnRepeat; }
	double learnRate() { return config._learnRate; }
	int inputNodes() { return config._inputNodes; }
	int hiddenNodes() { return config._hiddenNodes; }
	int outputNodes() { return config._outputNodes; }

	void initBuffers() {
		W_xh = vector< vector<double> > ( inputNodes() );
		for (size_t i = 0; i < W_xh.size(); i++)
			W_xh[i] = vector<double> ( hiddenNodes() );
		W_hy = vector< vector<double> > ( hiddenNodes() );
		for (size_t i = 0; i < W_hy.size(); i++)
			W_hy[i] = vector<double> ( outputNodes() );

		dW_xh = vector< vector<double> > ( inputNodes() );
		for (size_t i = 0; i < dW_xh.size(); i++)
			dW_xh[i] = vector<double> ( hiddenNodes() );
		dW_hy = vector< vector<double> > (hiddenNodes() );
		for (size_t i = 0; i < dW_hy.size(); i++)
			dW_hy[i] = vector<double> ( outputNodes() );

		H = vector<double> ( hiddenNodes() );
		Y = vector<double>( outputNodes() );
		biasH = vector<double> ( hiddenNodes() );
		biasY = vector<double> ( outputNodes() );
		dBiasH = vector<double> ( hiddenNodes() );
		dBiasY = vector<double> ( outputNodes() );
		errorH = vector<double> ( hiddenNodes() );
		errorY = vector<double> ( outputNodes() );
	}

	void setTrainingData() {
		X = vector<double> { 0.0, 0.0, 1.0, 1.0, 0.0,
						     0.0, 1.0, 1.0, 0.0, 0.0,
						     0.0, 0.0, 1.0, 1.0, 0.0,
						     0.0, 0.0, 0.0, 1.0, 0.0,
						     1.0, 1.0, 1.0, 0.0, 1.0};
	}

	void setValidData() {
		T = vector<double> { 1.0, 0.0, 1.0, 0.0, 0.0 };
	}

	void runNN() {
		beginTime = clock();

		for (int iter = 0; iter < learnRepeat(); iter++) {
			//input->hidden process
			for (int h = 0; h < hiddenNodes(); h++) {
				double sum = 0.0;
				for (int i = 0; i < inputNodes(); i++)
					sum += X[i] * W_xh[i][h];
				//apply activity function
				H[h] = 1.0 / (1 + exp(-(sum - biasH[h])));
			}

			//hidden->output process
			for (int j = 0; j < outputNodes(); j++) {
				double sum = 0.0;
				for (int h = 0; h < hiddenNodes(); h++)
					sum += H[h] * W_hy[h][j];
				//apply activity function
				Y[j] = 1.0 / (1 + exp(-(sum - biasY[j])));
			}

			//compute output layer error
			for (int j = 0; j < outputNodes(); j++)
				errorY[j] = Y[j] * (1.0 - Y[j]) * (T[j] - Y[j]);

			//compute hidden layer error
			for (int h = 0; h < hiddenNodes(); h++) {
				double sum = 0.0;
				for (int j = 0; j < outputNodes(); j++)
					sum += W_hy[h][j] * errorY[j];
				errorH[h] = H[h] * (1.0 - H[h]) * sum;
			}

			//compute delta Weight(H,J), delta BiasY
			//delta Weight(X,H) and delta BiasH
			for (int j = 0; j < outputNodes(); j++)
				for (int h = 0; h < hiddenNodes() ; h++)
					dW_hy[h][j] = learnRate() * errorY[j] * H[h];
			for (int j = 0; j < outputNodes(); j++)
				dBiasY[j] = -learnRate() * errorY[j];
			for (int h = 0; h < hiddenNodes(); h++)
				for (int i = 0; i < inputNodes(); i++)
					dW_xh[i][h] = learnRate() * errorH[h] * X[i];
			for (int h = 0; h < hiddenNodes(); h++)
				dBiasH[h] = -learnRate() * errorH[h];

			//update Why, BiasY, Wxh and BiasH
			for (int j = 0; j < outputNodes(); j++)
				for (int h = 0; h < hiddenNodes(); h++)
					W_hy[h][j] += dW_hy[h][j];
			for (int j = 0; j < outputNodes(); j++)
				biasY[j] += dBiasY[j];
			for (int h = 0; h < hiddenNodes(); h++)
				for (int i = 0; i < inputNodes(); i++)
					W_xh[i][h] += dW_xh[i][h];
			for (int h = 0; h < hiddenNodes(); h++)
				biasH[h] += dBiasH[h];
		}

		endTime = clock();
		elaspeTime = double(endTime - beginTime) / CLOCKS_PER_SEC;
	}

	void printResult() {
		cout << "Original valid:" << endl;
		for (size_t i = 0; i < T.size(); i++)
			cout << T[i] << "  ";
		cout << endl << endl;

		cout << "NN predict:" << endl;
		for (size_t i = 0; i < Y.size(); i++)
			cout << Y[i] << "  ";
		cout << endl << endl;

		cout << "Program runs : " << elaspeTime << " sec.\n";
	}
};


int main()
{
	NN_CONFIG myConfig1 = {20000, 0.01, 25, 5, 5};
	NN_CONFIG myConfig2 = { 500, 0.05, 25, 5, 5 };

	NeuralNetwork nnTest1 = NeuralNetwork(myConfig1);
	NeuralNetwork nnTest2 = NeuralNetwork(myConfig2);

	nnTest1.initBuffers(); nnTest2.initBuffers();
	nnTest1.setTrainingData(); nnTest2.setTrainingData();
	nnTest1.setValidData(); nnTest2.setValidData();
	nnTest1.runNN(); nnTest2.runNN();
	nnTest1.printResult(); nnTest2.printResult();


	nnTest1.~NeuralNetwork(); nnTest2.~NeuralNetwork();


	return EXIT_SUCCESS;
}
