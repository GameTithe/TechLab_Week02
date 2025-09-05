#pragma once

struct FVector;
struct FVector4;
 
/**
* Row(Vector) Major Matrix
* A four-dimensional Matrix 
*/
struct FMatrix
{ 
public:
	FMatrix();
	FMatrix(FVector4 col0, FVector4 col1, FVector4 col2, FVector4 col3);

public:
	void Transpose();
	 
	void RowToColumn() { Transpose(); }
	void ColumnToRow() { Transpose(); }

	FMatrix  operator+(const FMatrix& rhs) const;
	FMatrix& operator+=(const FMatrix& rhs);
	FMatrix  operator-(const FMatrix& rhs) const;
	FMatrix& operator-=(const FMatrix& rhs);

	FMatrix operator*(const FMatrix& rhs) const;   
	FMatrix  operator*(const float rhs) const; 

	FMatrix& operator*=(const float rhs); 

	static const FMatrix Identity;

public:
	static FMatrix MakeScaleMatrix(float scale);
	static FMatrix MakeScaleMatrix(float scale0, float scale1, float scale2); 

	static FMatrix MakeRotationXMatrix(float degree);
	static FMatrix MakeRotationYMatrix(float degree);
	static FMatrix MakeRotationZMatrix(float degree);
	  
	static FMatrix MakeTranslationMatrix(FVector4 tranlation);

public:
	float M[4][4];

private:
	const int rowCount = 4;
	const int columnCount = 4; 
};
 