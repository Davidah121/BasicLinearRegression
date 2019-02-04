#include <iostream>
#include "Matrix.h"
#include "BasicIO.h"
#include <vector>
#include <string>
#include <math.h>

struct point
{
	float x;
	float y;
};


std::vector<point> pointsOfEquation = std::vector<point>();

void getValues(char* filename)
{
	BasicIO file(filename);

	std::string tempData = "";
	char byte = '\0';

	bool xSet = false;

	point tempPoint;

	while (!file.isEndOfFile())
	{
		byte = file.readByte();

		if (byte != ',')
		{
			tempData += byte;
		}
		else
		{
			if (xSet == false)
			{
				tempPoint.x = std::stof(tempData);
				tempData = "";
				xSet = true;
			}
			else
			{
				tempPoint.y = std::stof(tempData);
				tempData = "";
				xSet = false;

				pointsOfEquation.push_back(tempPoint);
			}
		}
	}

	file.close();
}

void doLinearRegression()
{
	//float* values = new float[pointsOfEquation.size()];
	//B = Inverse( Transpose(X) * X ) * Transpose(X) * Y;

	Matrix X = Matrix(pointsOfEquation.size(), 2);
	Matrix Y = Matrix(pointsOfEquation.size(), 1);
	Matrix TransposeX = Matrix(2, pointsOfEquation.size());

	for (int i = 0; i < pointsOfEquation.size(); i++)
	{
		X[i][0] = 1;
		X[i][1] = pointsOfEquation[i].x;

		TransposeX[0][i] = 1;
		TransposeX[1][i] = pointsOfEquation[i].x;

		Y[i][0] = pointsOfEquation[i].y;
	}

	Matrix Answer = (TransposeX*X).getInverse() * TransposeX * Y;
	
	std::cout << "XT * X Transpose Matrix" << std::endl;
	for (int i = 0; i < Answer.getRows(); i++)
	{
		for (int i2 = 0; i2 < Answer.getCols(); i2++)
		{
			std::cout << Answer[i][i2] << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << "Y - Intercept: " << Answer[0][0] << std::endl;
	std::cout << "Slope: " << Answer[1][0] << std::endl;
}

void main(int sizeOfInput, char** input)
{
	for (int i = 0; i < sizeOfInput; i++)
	{
		std::cout << input[i] << std::endl;
	}

	if (sizeOfInput > 1)
	{
		getValues(input[1]);
		doLinearRegression();
	}
	else
	{
		std::cout << "Not enough inputs" << std::endl;
		std::cout << "Requires a file with values separated by commas with an ending comma" << std::endl;
	}

	system("pause");
}