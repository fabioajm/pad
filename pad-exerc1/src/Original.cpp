//============================================================================
// Name        : teste.cpp
// Author      : Fabio
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <sys/time.h>
using namespace std;

double get_wall_time() {
	struct timeval time;
	if (gettimeofday(&time, NULL)) {
		//  Handle error
		return 0;
	}
	return (double) time.tv_sec + (double) time.tv_usec * .000001;
}

double get_cpu_time() {
	return (double) clock() / CLOCKS_PER_SEC;
}

int imod(int n, int mod) {
	return n % mod;

}

void arrayOriginal(int size) {
	int a[size][size], b[size][size], c[size][size];
	double startWallTime, startCpuTime;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a[i][j] = 10 * i + 50 * j;
			b[i][j] = 10 * i + 50 * j;
			c[i][j] = 0;
		}
	}

	startCpuTime = get_cpu_time();
	startWallTime = get_wall_time();

	for (int k = 0; k < size; k++) {
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}

	cout << "Metrics" << endl;
	cout << "Wall Time = " << get_wall_time() - startWallTime << endl;
	cout << "CPU Time  = " << get_cpu_time() - startCpuTime << endl;
	cout << "Array size = " << size << endl;

}

void permutaLoopsArray(int size) {
	int a[size][size], b[size][size], c[size][size];
	double startWallTime, startCpuTime;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a[i][j] = 10 * i + 50 * j;
			b[i][j] = 10 * i + 50 * j;
			c[i][j] = 0;
		}
	}

	startCpuTime = get_cpu_time();
	startWallTime = get_wall_time();

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			for (int k = 0; k < size; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}

	cout << "Metrics exchange loops" << endl;
	cout << "Wall Time = " << get_wall_time() - startWallTime << endl;
	cout << "CPU Time  = " << get_cpu_time() - startCpuTime << endl;
	cout << "Array size = " << size << endl;
}

void unrolling(int size) {
	int a[size][size], b[size][size], c[size][size];
	double startWallTime, startCpuTime;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a[i][j] = 10 * i + 50 * j;
			b[i][j] = 10 * i + 50 * j;
			c[i][j] = 0;
		}
	}

	startCpuTime = get_cpu_time();
	startWallTime = get_wall_time();

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			int kk = imod(size, 4);
			for (int k = 0; k < kk; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}

			double temp0 = 0.0;
			double temp1 = 0.0;
			double temp2 = 0.0;
			double temp3 = 0.0;
			for (int k = 0 + kk; k < size; k += 4) {
				temp0 = temp0 + a[i][k] * b[k][j];
				temp1 = temp1 + a[i][k + 1] * b[k + 1][j];
				temp2 = temp2 + a[i][k + 2] * b[k + 2][j];
				temp3 = temp3 + a[i][k + 3] * b[k + 3][j];
			}
			c[i][j] = c[i][j] + temp0 + temp1 + temp2 + temp3;
		}
	}

	cout << "Metrics unrolling" << endl;
	cout << "Wall Time = " << get_wall_time() - startWallTime << endl;
	cout << "CPU Time  = " << get_cpu_time() - startCpuTime << endl;
	cout << "Array size = " << size << endl;
}

int main(int argc, char *argv[]) {
	int size;
	cout << "Enter the array size :" << endl;
	cin >> size;

	arrayOriginal(size);

	permutaLoopsArray(size);

	unrolling(size);

	cout << "Mod = " << imod(size, 4) << endl;

	return 0;
}

