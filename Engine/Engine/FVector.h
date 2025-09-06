#pragma once

/**
* FVector
* A three-dimensional vector
*/
 
struct FMatrix; 

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

	static FVector Lerp(const FVector& v1, const FVector& v2, float t);  

	static const FVector RIGHT;
	static const FVector LEFT;
	static const FVector FRONT; 
	static const FVector BACK;
	static const FVector UP;
	static const FVector DOWN;

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
* A four-dimensional Vector
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

	static FVector4 Lerp(const FVector4& v1, const FVector4& v2, float t);

	static const FVector4 RIGHT;
	static const FVector4 LEFT;
	static const FVector4 FRONT;
	static const FVector4 BACK;
	static const FVector4 UP;
	static const FVector4 DOWN;

public:
	FVector4 operator*		(const FMatrix& rhs) const;

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