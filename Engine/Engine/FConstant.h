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
	int Pick;
	float Padding[3];
};

struct FObjectPicking
{
	int ObjectID;
	float Padding[3];
	 
};