#pragma once
#include "FMatrix.h"
#include "FVector.h"

struct FMVPConstants
{
	FMatrix Model;
	FMatrix View;
	FMatrix Perspective;
};
struct FConstants
{
	FVector Offset;
	float Radius;  
};

struct FObjectPicking
{
	int Pick;
	int ObjectID; 
	int Padding[2];
	       
}; 