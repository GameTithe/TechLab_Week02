#pragma once
#include "FVector.h"
#include "USceneComponent.h"

class CameraComponent : public USceneComponent
{
public:
	void UpdateAngleAndDirection(int mouseX,int mouseY, float screenWidth,float screenHeight);
private:
	float MouseNdcX;
	float MouseNdcY;

	// Camera의 local 회전각도
	float Yaw; // y축
	float Pitch; // x축

	// 카메라가 바라보는 방향 기준에서 각 방향
	FVector Up;
	FVector Right;
	FVector Front;
};