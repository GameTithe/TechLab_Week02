#pragma once
#include "FVector.h"
#include "FMatrix.h"

struct FVertex
{
	FVector position;
	FVector4 color;
	//FVector2 texcoord;
};

struct FMVP
{
	FMatrix model;
	FMatrix view;
	FMatrix projection;
};