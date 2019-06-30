
#include "pch.h"
#include <iostream>
#include <omp.h>

int main()
{
	int a = 0;
	//#pragma omp simd
	//#pragma parallel for lastprivate(a) num_threads(100)
	#pragma omp target teams distribute parallel for
	{
		for (int i = 0; i < 1000; i++) {
			std::cout << a << std::endl;
			a += i;
		}
	}
}

