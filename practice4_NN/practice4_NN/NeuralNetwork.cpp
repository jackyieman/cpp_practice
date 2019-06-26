#include "pch.h"
#include "NeuralNetwork.h"



NeuralNetwork::NeuralNetwork() :config(500, 0.05, 25, 5, 5){}
NeuralNetwork::NeuralNetwork(const NN_CONFIG configRef) : config(configRef._learnRepeat, configRef._learnRate, configRef._inputNodes, configRef._hiddenNodes, configRef._outputNodes) {}
NeuralNetwork::~NeuralNetwork(){}

int NeuralNetwork::learnRepeat() const{ return config._learnRepeat; }
double NeuralNetwork::learnRate() const { return config._learnRate; }
int NeuralNetwork::inputNodes() const { return config._inputNodes; }
int NeuralNetwork::hiddenNodes() const { return config._hiddenNodes; }
int NeuralNetwork::outputNodes() const { return config._outputNodes; }

void NeuralNetwork::readFileToBuffer(string fileName, vector<double> &output, int limit) {
	fstream file;
	file.open(fileName, std::ios::in);

	if (file.is_open()) {
		double value{ 0.0 };
		int counter{ 0 };
		do {
			if (counter >= limit)
				break;
			file >> value;
			//cout << std::fixed << std::setprecision(5) << value << endl;
			output.push_back(value);
			counter++;
		} while (!file.eof());
	}
	else
		cerr << "Read file fail: Can't open file.\n";
	file.close();
}

void NeuralNetwork::initBuffers() {
	W_xh = vector< vector<double> >(inputNodes());
	for (size_t i = 0; i < W_xh.size(); i++)
		W_xh[i] = vector<double>(hiddenNodes());
	W_hy = vector< vector<double> >(hiddenNodes());
	for (size_t i = 0; i < W_hy.size(); i++)
		W_hy[i] = vector<double>(outputNodes());

	dW_xh = vector< vector<double> >(inputNodes());
	for (size_t i = 0; i < dW_xh.size(); i++)
		dW_xh[i] = vector<double>(hiddenNodes());
	dW_hy = vector< vector<double> >(hiddenNodes());
	for (size_t i = 0; i < dW_hy.size(); i++)
		dW_hy[i] = vector<double>(outputNodes());

	H = vector<double>(hiddenNodes());
	Y = vector<double>(outputNodes());
	biasH = vector<double>(hiddenNodes());
	biasY = vector<double>(outputNodes());
	dBiasH = vector<double>(hiddenNodes());
	dBiasY = vector<double>(outputNodes());
	errorH = vector<double>(hiddenNodes());
	errorY = vector<double>(outputNodes());
}

void NeuralNetwork::setTrainingData(string fileName) {
	X = vector<double>{};
	readFileToBuffer(fileName, X, inputNodes());
 }

void NeuralNetwork::setValidData(string fileName) {
	T = vector<double>{};
	readFileToBuffer(fileName, T, outputNodes());
}

void NeuralNetwork::runNN() {
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
			for (int h = 0; h < hiddenNodes(); h++)
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

void NeuralNetwork::printResult() const{
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