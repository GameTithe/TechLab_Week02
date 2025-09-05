#pragma once
#include "FMatrix.h"
#include "FVector.h"

struct FMVPConstants
{
	FMatrix Model;
	FMatrix View;
	FMatrix Projection;
};
struct FConstants
{
	FVector Offset;
	float Radius;
	//float Pad;
};