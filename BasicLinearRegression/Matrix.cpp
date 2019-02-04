#include "Matrix.h"
#include <iostream>

const Matrix Matrix::invalidMatrix = Matrix();

Matrix::Matrix()
{
	rows = 0;
	cols = 0;
	data = nullptr;
}

Matrix::Matrix(int row, int col)
{
	rows = row;
	cols = col;

	if (rows != 0 && cols != 0)
	{
		data = new double*[rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
		}
	}
}

Matrix::Matrix(const Matrix & B)
{
	rows = B.rows;
	cols = B.cols;
	if (rows != 0 && cols != 0)
	{
		data = new double*[rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
		}

		for (int i = 0; i < rows; i++)
		{
			for (int i2 = 0; i2 < cols; i2++)
			{
				data[i][i2] = B.data[i][i2];
			}
		}
	}
}


Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		if(data[i]!=nullptr)
			delete[] data[i];
	}

	if(data!=nullptr)
		delete[] data;
}

Matrix Matrix::getTranspose()
{
	Matrix m = Matrix(cols, rows);
	for (int i = 0; i < rows; i++)
	{
		for (int i2 = 0; i2 < cols; i2++)
		{
			m[i2][i] = data[i][i2];
		}
	}

	return m;
}

double Matrix::getDeterminate()
{
	if (rows == cols)
	{
		if (rows == 2)
		{
			return (data[0][0] * data[1][1]) - (data[1][0] * data[0][1]);
		}
		else
		{
			double sumValue = 0;
			for (int i = 0; i < rows; i++)
			{
				if (i % 2 == 0)
				{
					sumValue += data[i][0] * getMatrixOfMinors(i, 0).getDeterminate();
				}
				else
				{
					sumValue -= data[i][0] * getMatrixOfMinors(i, 0).getDeterminate();
				}
			}

			return sumValue;
		}
	}
	return 0;
}

Matrix Matrix::getMatrixOfMinors(int row, int col)
{
	Matrix m = Matrix(rows - 1, cols - 1);

	int currentRow = 0;
	int currentCol = 0;

	for (int i = 0; i < rows; i++)
	{
		currentCol = 0;

		for (int i2 = 0; i2 < cols; i2++)
		{
			if (i != row && i2 != col)
			{
				m[currentRow][currentCol] = data[i][i2];
				currentCol++;
			}
		}

		if (i != row)
		{
			currentRow++;
		}
	}

	return m;
}


Matrix Matrix::getInverse()
{
	double det = getDeterminate();

	if (det != 0)
	{
		Matrix m = Matrix(rows, cols);

		if (m.getCols() == 2 && m.getRows() == 2)
		{
			m[0][0] = data[1][1];
			m[1][1] = data[0][0];
			m[1][0] = -data[1][0];
			m[0][1] = -data[0][1];

			return m * (1 / det);
		}
		else
		{
			double multValue = 1;
			for (int i = 0; i < rows; i++)
			{
				for (int i2 = 0; i2 < cols; i2++)
				{
					m[i][i2] = getMatrixOfMinors(i, i2).getDeterminate();
					
					if ((i + i2) % 2 == 1)
					{
						m[i][i2] *= -1;
					}
				}
			}
			Matrix m2 = m.getTranspose();
			
			return m2*(1 / det);
		}
	}
	else
	{
		return Matrix();
	}
}

bool Matrix::operator==(Matrix B)
{
	bool same = true;

	if (rows == B.getRows() && cols == B.getCols())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int i2 = 0; i2 < cols; i2++)
			{
				if (data[i][i2] != B[i][i2])
				{
					same = false;
					break;
				}
			}
		}
		
	}
	else
	{
		return false;
	}

	return same;
}

double* Matrix::operator[](int row)
{
	return data[row];
}

int Matrix::getRows()
{
	return rows;
}

int Matrix::getCols()
{
	return cols;
}

Matrix Matrix::operator+(Matrix B)
{
	if (rows == B.getRows() && cols == B.getCols())
	{
		Matrix m = Matrix(rows, cols);

		for (int i = 0; i < rows; i++)
		{
			for (int i2 = 0; i2 < cols; i2++)
			{
				m[i][i2] = data[i][i2] + B[i][i2];
			}
		}

		return m;
	}
	return Matrix();
}

Matrix Matrix::operator-(Matrix B)
{
	if (rows == B.getRows() && cols == B.getCols())
	{
		Matrix m = Matrix(rows, cols);

		for (int i = 0; i < rows; i++)
		{
			for (int i2 = 0; i2 < cols; i2++)
			{
				m[i][i2] = data[i][i2] - B[i][i2];
			}
		}

		return m;
	}
	return Matrix();
}

Matrix Matrix::operator-()
{
	Matrix m = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int i2 = 0; i2 < cols; i2++)
		{
			m[i][i2] = -data[i][i2];
		}
	}

	return m;
}

Matrix Matrix::operator*(Matrix B)
{
	if (cols == B.getRows())
	{
		Matrix m = Matrix(rows, B.getCols());
		
		double sumValue = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int i2 = 0; i2 < B.getCols(); i2++)
			{
				sumValue = 0;

				for (int r = 0; r < cols; r++)
				{
					sumValue += data[i][r] * B[r][i2];
				}

				//std::cout << sumValue << std::endl;
				m[i][i2] = sumValue;
			}
		}

		return m;
	}

	return Matrix();
}

Matrix Matrix::operator*(double B)
{
	Matrix m = Matrix(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int i2 = 0; i2 < cols; i2++)
		{
			m[i][i2] = B * data[i][i2];
		}
	}
	return m;
}
