#pragma once

#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define RANDOM_MAX (100)
#define RANDOM_MIN (1)

void writeRandomOutput(const char *outFileName, int lines, int elements);
void writeRandomOutput(const char *outFileName, int lines, int elements) {

	fstream file;
	file.open(outFileName, ios::out | ios::trunc);
	srand((unsigned)time(NULL));

	if (file.is_open()) {
		//write header
		file << lines << ' ' << elements << '\n';

		//write content
		for (int i{ 0 }; i < lines; i++) {
			for (int j{ 0 }; j < elements; j++)
				file << rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN << ' ';
			file << "\n";
		}

	}
	else
		cerr << "Write file fail: Can't open file.\n";
	file.close();
	cout << "Write file success.\n";
}
