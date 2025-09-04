#include "FVector.h"
#include <cmath>
#include <cassert>

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
	return sqrt(X * X + Y * Y + Z * Z);
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
		const float invLen = 1 / sqrt(len2);
		X *= invLen;
		Y *= invLen;
		Z *= invLen;
	}
	else
	{
		X = 0.0f; Y = 0.0f; Z = 0.0f;
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
