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

bool FMatrix::Inverse(FMatrix& out) const {
	float eps = 1e-10; 
	double inv[16];
	double m[16];

	// FMatrix → 1차원 배열 (row-major 라고 가정)
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i * 4 + j] = static_cast<double>(M[i][j]);

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	double det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	if (std::fabs(det) < eps) return false;

	det = 1.0 / det;
	for (int i = 0; i < 16; i++)
		inv[i] *= det;

	// 1차원 배열 → FMatrix
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			out.M[i][j] = static_cast<float>(inv[i * 4 + j]);

	return true;
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

FMatrix FMatrix::MakeLookAt(FVector eye, FVector at, FVector up)
{
	FVector front = at - eye;
	front.Normalize();

	FVector right = up.Cross(front);
	right.Normalize();

	up = front.Cross(right);
	
	return FMatrix( 
		FVector4(right.X, right.Y, right.Z, 0.0f),
		FVector4(up.X, up.Y, up.Z, 0.0f),
		FVector4(front.X, front.Y, front.Z, 0.0f),
		FVector4(-right.Dot(eye), -up.Dot(eye), -front.Dot(eye), 1.0f));
}
   
FMatrix FMatrix::MakePerspectiveMatrix(float fovy, float aspect, float zNear, float zFar)
{
	const float rad = fovy * (PI / 180.0f);
	const float yScale = 1.0f / std::tan(rad * 0.5f);
	const float xScale = yScale / aspect;
	 
	const float A = zFar / (zFar - zNear);
	const float B = -zNear * A;

	// 열 기준 배치:
	// [ xS   0    0   0 ]
	// [ 0    yS   0   0 ]
	// [ 0    0    A   1 ]
	// [ 0    0    B   0 ]
	// => clip: x′=xS*x, y′=yS*y, z′=A*z + B, w′=z
	return FMatrix(
		FVector4(xScale, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, yScale, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, A, 1.0f),
		FVector4(0.0f, 0.0f, B, 0.0f)
	);
}
 
#pragma region Legacy
/*
// x: forward 
// y: right
// z: up
static FMatrix MakeLookAt(FVector eye, FVector at, FVector up)
{
	// X
	FVector forward = at - eye; 
	forward.Normalize();

	// Y
	FVector right = forward.Cross(up);
	right.Normalize();

	// Z
	FVector up = right.Cross(forward);
	up.Normalize();

	FMatrix camInvVM
	{
		FVector4(forward.X, right.X, up.X, 0.0f),
		FVector4(forward.Y, right.Y, up.Y, 0.0f),
		FVector4(forward.Z, right.Z, up.Z, 0.0f),
		FVector4(0.0f, 0.0f, 0.0f, 1.0f)
	}; 
	camInvVM.Transpose();

	FMatrix camInvTM
	{
		FVector4(1.0f, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, 1.0f, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, 1.0f, 0.0f),
		FVector4(-eye.X, -eye.Y, -eye.Z, 1.0f)
	};

	return camInvTM* camInvVM; 
}

FMatrix FMatrix::MakePerspectiveMatrix(float fovz, float aspect, float zNear, float zFar)
{
	const float sy = 1.0f / std::tan(fovz * 0.5f);
	const float sx = sy / aspect;
	const float q = zFar / (zFar - zNear);
	const float qn = -zNear * q;

	return FMatrix(
		FVector4(q, 0, 0, qn),
		FVector4(0.0f, sy, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, sx, 0.0f),
		FVector4(1.0f, 0.0f, 0.0f, 0.0f)
	);
}
*/
#pragma endregion
