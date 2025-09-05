#include "FMatrix.h"

#include "FVector.h" 

#include <cmath>
#include <utility>
#include <cassert>

const float PI = 3.1415926535f;

const FMatrix FMatrix::Identity = { FVector4(1,0,0,0),FVector4(0,1,0,0),FVector4(0,0,1,0),FVector4(0,0,0,1) };


FMatrix::FMatrix()
{
	M[0][0] = 0.0f;
	M[1][0] = 0.0f;
	M[2][0] = 0.0f;
	M[3][0] = 0.0f;

	M[0][1] = 0.0f;
	M[1][1] = 0.0f;
	M[2][1] = 0.0f;
	M[3][1] = 0.0f;

	M[0][2] = 0.0f;
	M[1][2] = 0.0f;
	M[2][2] = 0.0f; 
	M[3][2] = 0.0f;

	M[0][3] = 0.0f;
	M[1][3] = 0.0f;
	M[2][3] = 0.0f;
	M[3][3] = 0.0f; 
} 
 
FMatrix::FMatrix(FVector4 col0, FVector4 col1, FVector4 col2, FVector4 col3)
{
	M[0][0] = col0.X;
	M[1][0] = col0.Y;
	M[2][0] = col0.Z;
	M[3][0] = col0.W;

	M[0][1] = col1.X;
	M[1][1] = col1.Y;
	M[2][1] = col1.Z;
	M[3][1] = col1.W;

	M[0][2] = col2.X;
	M[1][2] = col2.Y;
	M[2][2] = col2.Z; 
	M[3][2] = col2.W;

	M[0][3] = col3.X;
	M[1][3] = col3.Y;
	M[2][3] = col3.Z;
	M[3][3] = col3.W;
}

void FMatrix::Transpose()
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = i + 1; j < columnCount; j++)
		{
			std::swap(M[i][j], M[j][i]);
		}
	}
}  

FMatrix FMatrix::operator+(const FMatrix& rhs) const
{
	FMatrix temp; 
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			temp.M[i][j] = M[i][j] + rhs.M[i][j];
		}
	}
	return temp;
}

FMatrix& FMatrix::operator+=(const FMatrix& rhs)
{
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			M[i][j] += rhs.M[i][j];
		}
	}
	return *this;
}

FMatrix FMatrix::operator-(const FMatrix& rhs) const
{
	FMatrix temp;
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			temp.M[i][j] = M[i][j] - rhs.M[i][j];
		}
	}
	return temp;
}

FMatrix& FMatrix::operator-=(const FMatrix& rhs)
{
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			M[i][j] -= rhs.M[i][j];
		}
	}
	return *this;
}

FMatrix FMatrix::operator*(const FMatrix& rhs) const
{
	assert(columnCount == rhs.rowCount);

	FMatrix temp;
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < rhs.columnCount; ++j)
		{
			temp.M[i][j] = 0.0f;
			for (int k = 0; k < columnCount; ++k)
			{
				temp.M[i][j] += M[i][k] * rhs.M[k][j];
			}
		}
	}
	return temp;
}
 


FMatrix FMatrix::operator*(const float rhs) const
{ 
	FMatrix temp;
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			temp.M[i][j] = M[i][j] * rhs;	
		}
	}
	return temp;
}


FMatrix& FMatrix::operator*=(const float rhs)
{  
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < columnCount; ++j)
		{
			M[i][j] = M[i][j] * rhs;	
		}
	}  
	return *this;
}



FMatrix FMatrix::MakeScaleMatrix(float scale)
{
	return FMatrix(
		FVector4(scale, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, scale, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, scale, 0.0f),
		FVector4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}


FMatrix FMatrix::MakeScaleMatrix(float scale0, float scale1, float scale2)
{
	return FMatrix(
		FVector4(scale0, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, scale1, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, scale2, 0.0f),
		FVector4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}

FMatrix FMatrix::MakeRotationXMatrix(float degree)
{
	float rad = degree * (PI / 180.0f);
	float c = std::cos(rad);
	float s = std::sin(rad);

	return FMatrix(
		FVector4(1.0f, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, c, s, 0.0f),
		FVector4(0.0f, -s, c, 0.0f),
		FVector4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}

FMatrix FMatrix::MakeRotationYMatrix(float degree)
{
	float rad = degree * (PI / 180.0f);
	float c = std::cos(rad);
	float s = std::sin(rad); 

	return FMatrix(
		FVector4(c, 0.0f, -s, 0.0f),
		FVector4(0.0f, 1.0f, 0.0f, 0.0f),
		FVector4(s, 0.0f, c, 0.0f),
		FVector4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}

FMatrix FMatrix::MakeRotationZMatrix(float degree)
{
	float rad = degree * (PI / 180.0f);
	float c = std::cos(rad);
	float s = std::sin(rad); 

	return FMatrix(
		FVector4(c, s, 0.0f, 0.0f),
		FVector4(-s, c, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, 1.0f, 0.0f),
		FVector4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}
 
FMatrix FMatrix::MakeTranslationMatrix(FVector4 tranlation)
{
	return FMatrix(
		FVector4(1.0f, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, 1.0f, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, 1.0f, 0.0f),
		FVector4(tranlation.X, tranlation.Y, tranlation.Z, 1.0f)
	);
}
