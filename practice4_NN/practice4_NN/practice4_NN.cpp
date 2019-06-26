#include "pch.h"
#include "NeuralNetwork.h"

int main()
{
	NN_CONFIG myConfig1 = { 20000, 0.01, 25, 5, 5 };
	NN_CONFIG myConfig2 = { 500, 0.05, 25, 5, 5 };

	NeuralNetwork *nnTest1 = new NeuralNetwork(myConfig1);
	NeuralNetwork nnTest2 = NeuralNetwork(myConfig2);

	nnTest1->initBuffers();
	nnTest2.initBuffers();
	nnTest1->setTrainingData("train.txt");
	nnTest2.setTrainingData("train.txt");
	nnTest1->setValidData("target.txt");	
	nnTest2.setValidData("target.txt");

	nnTest1->runNN();			nnTest2.runNN();
	nnTest1->printResult();		nnTest2.printResult();

	nnTest1->~NeuralNetwork();	nnTest2.~NeuralNetwork();
	delete nnTest1;

	return EXIT_SUCCESS;
}
