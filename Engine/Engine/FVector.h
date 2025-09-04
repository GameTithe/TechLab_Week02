#pragma once
   
struct FVector
{
public:
	FVector() : X(0.0f), Y(0.0f), Z(0.0f) {}
	FVector(float x, float y, float z) : X(x), Y(y), Z(z) {}


	float Dot(const FVector& rhs) const;
	FVector Cross(const FVector& rhs) const;
	float Length() const;
	float LengthSquared() const;
	void Normalize(); 

public:
	FVector operator+	(const FVector& rhs) const;
	FVector& operator+= (const FVector& rhs); 
	FVector operator-	(const FVector& rhs) const;
	FVector& operator-= (const FVector& rhs); 
	FVector operator*	(const FVector& rhs) const;
	FVector& operator*= (const FVector& rhs);
	FVector operator/	(const FVector& rhs) const;
	FVector& operator/= (const FVector& rhs);
	  
	FVector operator*	(const float rhs) const;
	FVector& operator*= (const float rhs);  
	FVector operator/	(const float rhs) const;
	FVector& operator/= (const float rhs); 
	 
public:
	float X, Y, Z;
};

inline FVector operator* (float lhs, const FVector& rhs) 
{
	return FVector(lhs * rhs.X, lhs * rhs.Y, lhs * rhs.Z);
}

struct FVector4
{
public : 
	float X, Y, Z, W;

	float Dot(const FVector4& Other);
	float Length();
	float Length3();
};