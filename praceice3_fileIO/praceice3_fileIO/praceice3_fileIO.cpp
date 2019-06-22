#include "pch.h"
#include <iostream>

#include "randomFun.h"
#include "readFile.h"

void printBuffer(int **&buffer, int lines, int elements) {
	cout << "\n";
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < elements; j++)
			cout << buffer[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}


int main(int argc, char *argv[])
{
	#define LINES (5)
	#define ELEMENTS (15)

	const char *outputFileName;
	if (argc == 1) {
		cout << "You must determine output file name.\n";
		return EXIT_FAILURE;
	}
	else
		outputFileName = argv[1];

	//write test bench
	cout << "start write file...\n";
	writeRandomOutput(outputFileName, LINES, ELEMENTS);

	//init buffer
	cout << "start read file...\n";
	int **buffer = new int*[LINES];
	for (int i{ 0 }; i < LINES; i++)
		buffer[i] = new int[ELEMENTS];
	int **&bufferRef = buffer;

	//do process
	readFile(outputFileName, bufferRef);
	printBuffer(bufferRef, LINES, ELEMENTS);


	//release buffer
	for (int i{ 0 }; i < LINES; i++)
		delete[] buffer[i];
	delete[] buffer;
	cout << "delete buffer success.\n";



	return EXIT_SUCCESS;
}
