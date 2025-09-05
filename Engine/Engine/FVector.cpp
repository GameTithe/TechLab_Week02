#include "FVector.h"
#include <cmath>
#include <cassert>

/**
* FVector 
* A three-dimensional vector.
*/
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
	W /= 0.0f;

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
	W /= 0.0f;

	return *this;
}