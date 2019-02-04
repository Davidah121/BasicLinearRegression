#pragma once
class Matrix
{
public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix &B);
	~Matrix();

	Matrix getTranspose();
	double getDeterminate();
	Matrix getMatrixOfMinors(int row, int col);
	Matrix getInverse();

	int getRows();
	int getCols();

	Matrix operator+(Matrix B);
	Matrix operator-(Matrix B);
	Matrix operator-();
	Matrix operator*(Matrix B);
	Matrix operator*(double B);

	bool operator==(Matrix B);

	double* operator[](int row);

	const static Matrix invalidMatrix;

private:
	double** data = nullptr;
	int rows = 0;
	int cols = 0;
};

