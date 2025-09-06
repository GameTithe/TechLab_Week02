#include "FVector.h"
#include <cmath>
#include <cassert>
#include "FMatrix.h"

/**
* FVector 
* A three-dimensional vector.
*/ 
const FVector FVector::RIGHT	{ 1.0f, 0.0f, 0.0f };
const FVector FVector::LEFT		{ -1.0f, 0.0f, 0.0f };
const FVector FVector::FRONT	{ 0.0f, 0.0f, 1.0f };
const FVector FVector::BACK	 	{ 0.0f, 0.0f, -1.0f };
const FVector FVector::UP		{ 0.0f, 1.0f, 0.0f };
const FVector FVector::DOWN		{ 0.0f, -1.0f, 0.0f };
const FVector FVector::ZERO		{ 0.0f, 0.0f, 0.0f };
const FVector FVector::ONE		{ 1.0f, 1.0f, 1.0f };

float FVector::Dot(const FVector& rhs) const
{
	return X * rhs.X + Y * rhs.Y + Z * rhs.Z;
}
 
FVector FVector::Cross(const FVector& rhs) const
{
	return FVector(Y * rhs.Z - Z * rhs.Y, 
					Z * rhs.X - X * rhs.Z, 
					X * rhs.Y - Y * rhs.X);
} 

float FVector::Length() const
{
	return std::sqrt(X * X + Y * Y + Z * Z);
}

float FVector::LengthSquared() const
{
	return X * X + Y * Y + Z * Z;
}

void FVector::Normalize()
{
	const float len2 = LengthSquared();
	if (len2 > 1e-10)
	{
		const float invLen = 1 / std::sqrt(len2);
		X *= invLen;
		Y *= invLen;
		Z *= invLen;
	}
	else
	{
		X = 0.0f; Y = 0.0f; Z = 0.0f;
	}
}

FVector FVector::Direction() const
{
	const float len2 = LengthSquared();
	if (len2 > 1e-10)
	{
		const float invLen = 1.0f / std::sqrt(len2);
		return FVector(X * invLen, Y * invLen, Z * invLen);
	}
	else
	{
		return FVector(0.0f, 0.0f, 0.0f);
	}
}

FVector FVector::Lerp(const FVector& v1, const FVector& v2, float t)
{
	return FVector(
		v1.X * (1 - t) + v2.X * t,
		v1.Y * (1 - t) + v2.Y * t,
		v1.Z * (1 - t) + v2.Z * t
	);
}
 

FVector FVector::operator+(const FVector& rhs) const
{
	return FVector(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
}

FVector& FVector::operator+=(const FVector& rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;

	return *this;
}

FVector FVector::operator-(const FVector& rhs) const
{
	return FVector(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
}

FVector& FVector::operator-=(const FVector& rhs)
{ 
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;

	return *this;
}

FVector FVector::operator*(const FVector& rhs) const
{
	return FVector(X * rhs.X, Y * rhs.Y, Z * rhs.Z); 
}

FVector& FVector::operator*=(const FVector& rhs)
{ 
	X *= rhs.X;
	Y *= rhs.Y;
	Z *= rhs.Z;

	return *this;
}

FVector FVector::operator/(const FVector& rhs) const
{
	assert(rhs.X != 0 && rhs.Y != 0 && rhs.Z != 0);

	return FVector(X / rhs.X, Y / rhs.Y, Z / rhs.Z);
}

FVector& FVector::operator/=(const FVector& rhs)
{
	assert(rhs.X != 0 && rhs.Y != 0 && rhs.Z != 0);

	X /= rhs.X;
	Y /= rhs.Y;
	Z /= rhs.Z;

	return *this;
} 

FVector FVector::operator*(const float rhs) const
{
	return FVector(X * rhs, Y * rhs, Z * rhs);
}

FVector& FVector::operator*=(const float rhs)
{ 
	X *= rhs;
	Y *= rhs;
	Z *= rhs;

	return *this;
}

FVector FVector::operator/(const float rhs) const
{
	assert(rhs != 0);

	return FVector(X / rhs, Y / rhs, Z / rhs);
}

FVector& FVector::operator/=(const float rhs)
{
	assert(rhs != 0);

	X /= rhs;
	Y /= rhs;
	Z /= rhs;

	return *this;
}

/**
* FVector4 (For Homogenous)
* A four-dimensional vector.
*/
const FVector4 FVector4::RIGHT	{ 1.0f, 0.0f, 0.0f, 0.0f};
const FVector4 FVector4::LEFT	{ -1.0f, 0.0f, 0.0f, 0.0f};
const FVector4 FVector4::FRONT	{ 0.0f, 0.0f, 1.0f, 0.0f };
const FVector4 FVector4::BACK	{ 0.0f, 0.0f, -1.0f, 0.0f};
const FVector4 FVector4::UP		{ 0.0f, 1.0f, 0.0f, 0.0f};
const FVector4 FVector4::DOWN	{ 0.0f, -1.0f, 0.0f, 0.0f};

float FVector4::Dot(const FVector4& rhs) const
{ 
	return X * rhs.X + Y * rhs.Y + Z * rhs.Z + W * rhs.W;
}

FVector4 FVector4::Cross(const FVector4& rhs) const
{ 
	return FVector4(
		Y * rhs.Z - Z * rhs.Y,
		Z * rhs.X - X * rhs.Z,
		X * rhs.Y - Y * rhs.X,
		0.0f
	);
}

float FVector4::Length() const
{ 
	return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

float FVector4::Length3() const
{
	return std::sqrt(X * X + Y * Y + Z * Z);
}

float FVector4::Length3Squared() const
{
	return X * X + Y * Y + Z * Z;
}

void FVector4::Normalize()
{
	const float len2 = Length3Squared();
	if (len2 > 1e-10f)
	{
		const float invLen = 1.0f / std::sqrt(len2);
		X *= invLen;
		Y *= invLen;
		Z *= invLen;
	}
	else
	{
		X = 0.0f; Y = 0.0f; Z = 0.0f;
	}
}

FVector4 FVector4::Direction() const
{
	const float len2 = Length3Squared();
	if (len2 > 1e-10f)
	{
		const float invLen = 1.0f / std::sqrt(len2);
		return FVector4(X * invLen, Y * invLen, Z * invLen, W);
	}
	else
	{
		return FVector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
} 

FVector4 FVector4::Lerp(const FVector4& v1, const FVector4& v2, float t)
{
	return FVector4(
		v1.X * (1 - t)  + v2.X * t,
		v1.Y * (1 - t)  + v2.Y * t,
		v1.Z * (1 - t)  + v2.Z * t,
		0.0f
	);
}

FVector4 FVector4::operator* (const FMatrix& rhs) const
{
	return FVector4(
		X * rhs.M[0][0] + Y * rhs.M[1][0] + Z * rhs.M[2][0] + W * rhs.M[3][0],
		X * rhs.M[0][1] + Y * rhs.M[1][1] + Z * rhs.M[2][1] + W * rhs.M[3][1],
		X * rhs.M[0][2] + Y * rhs.M[1][2] + Z * rhs.M[2][2] + W * rhs.M[3][2],
		X * rhs.M[0][3] + Y * rhs.M[1][3] + Z * rhs.M[2][3] + W * rhs.M[3][3]
	);
}

FVector4 FVector4::operator+(const FVector4& rhs) const
{
	return FVector4(X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W);
}

FVector4& FVector4::operator+=(const FVector4& rhs)
{
	X += rhs.X; 
	Y += rhs.Y; 
	Z += rhs.Z; 
	W += rhs.W;

	return *this;
}

FVector4 FVector4::operator-(const FVector4& rhs) const
{
	return FVector4(X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W);
}

FVector4& FVector4::operator-=(const FVector4& rhs)
{
	X -= rhs.X; 
	Y -= rhs.Y; 
	Z -= rhs.Z; 
	W -= rhs.W;

	return *this;
}

FVector4 FVector4::operator*(const FVector4& rhs) const
{
	return FVector4(X * rhs.X, Y * rhs.Y, Z * rhs.Z, W * rhs.W);
}

FVector4& FVector4::operator*=(const FVector4& rhs)
{
	X *= rhs.X; 
	Y *= rhs.Y;
	Z *= rhs.Z;
	W *= rhs.W;

	return *this;
}

FVector4 FVector4::operator/(const FVector4& rhs) const
{
	assert(rhs.X != 0.0f && rhs.Y != 0.0f && rhs.Z != 0.0f);
	
	return FVector4(X / rhs.X, Y / rhs.Y, Z / rhs.Z, 0.0f);
}

FVector4& FVector4::operator/=(const FVector4& rhs)
{
	assert(rhs.X != 0.0f && rhs.Y != 0.0f && rhs.Z != 0.0f);
	X /= rhs.X; 
	Y /= rhs.Y; 
	Z /= rhs.Z; 
	W = 0.0f;

	return *this;
} 

FVector4 FVector4::operator*(const float rhs) const
{
	return FVector4(X * rhs, Y * rhs, Z * rhs, 0.0f);
}

FVector4& FVector4::operator*=(const float rhs)
{
	X *= rhs; 
	Y *= rhs; 
	Z *= rhs; 
	W *= 0.0f;
	
	return *this;
}

FVector4 FVector4::operator/(const float rhs) const
{
	assert(rhs != 0.0f);

	return FVector4(X / rhs, Y / rhs, Z / rhs, 0.0f);
}

FVector4& FVector4::operator/=(const float rhs)
{
	assert(rhs != 0.0f);
	
	X /= rhs; 
	Y /= rhs; 
	Z /= rhs; 
	W = 0.0f;

	return *this;
}