#pragma once
#include <stdlib.h>
#include <time.h>

class matrix {
private:
	int** matr;
	int m = 0, n = 0;
public:
	matrix& operator+(const matrix* n);
	matrix& operator-(const matrix* n);
	matrix& operator*(const matrix* n);
	matrix(int, int);
	void init();
	void ranInit(int maxVal);
	void print();
	void input();
	void input(int* input_string);
	int getRows() const;
	int getColumns() const;
	int getElement(int m, int n);
	void writeElement(int m, int n, int s);
	matrix merge(matrix& a, matrix& b, matrix& c, matrix& d);
	void part(matrix& a, matrix& b, matrix& c, matrix& d);
	matrix add(matrix);
	matrix sub(matrix _M);
	matrix mult(matrix);
	matrix fast_mult(matrix* N);
	int maxTeilSum();
};

