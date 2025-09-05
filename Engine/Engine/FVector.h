#pragma once

/**
* FVector
* A three-dimensional vector
*/
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
	FVector Direction() const ;

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

/**
* FVector4 (For Homogenous)
* A four-dimensional vector
*/
struct FVector4
{
public: 
	FVector4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
	FVector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	 
	float Dot(const FVector4& rhs) const;
	FVector4 Cross(const FVector4& rhs) const;
	float Length() const;
	float Length3() const; 
	float Length3Squared() const;
	void Normalize();
	FVector4 Direction() const;

public:
	FVector4 operator+		(const FVector4& rhs) const;
	FVector4& operator+=	(const FVector4& rhs);
	FVector4 operator-		(const FVector4& rhs) const;
	FVector4& operator-=	(const FVector4& rhs);
	FVector4 operator*		(const FVector4& rhs) const;
	FVector4& operator*=	(const FVector4& rhs);
	FVector4 operator/		(const FVector4& rhs) const;
	FVector4& operator/=	(const FVector4& rhs);
		   
	FVector4 operator*		(const float rhs) const;
	FVector4& operator*=	(const float rhs);
	FVector4 operator/		(const float rhs) const;
	FVector4& operator/=	(const float rhs);


public:
	float X, Y, Z, W;

};