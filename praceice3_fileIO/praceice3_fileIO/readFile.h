#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readFile(const char *inputFileName,  int **&buffer);
void readFile(const char *inputFileName,  int **&buffer) {

	fstream file;
	file.open(inputFileName, ios::in);

	if (file.is_open()) {
		//read header
		int lines, elements;
		file >> lines >> elements;

		//read data and write to buffer
		int value{ 0 };
		int counter{ 0 };
		do {
			if (counter >= lines * elements)
				break;
			file >> value;
			buffer[counter / elements][counter % elements] = value;
			counter++;
		} while (!file.eof());

	}
	else
		cerr << "Read file fail: Can't open file.\n";
	file.close();
	cout << "Read file success.\n";


}
