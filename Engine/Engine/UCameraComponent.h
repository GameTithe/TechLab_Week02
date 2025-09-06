#pragma once
#include "FVector.h"
#include "FMatrix.h"
//#include "USceneComponent.h"

class UCameraComponent
{
public:
	UCameraComponent();
	//~UCameraComponent();

	void UpdateAngleAndDirection(int mouseX,int mouseY,float screenWidth,float screenHeight);

	void UpdatePosition();

	FVector GetUp() const
	{
		return Up;
	}
	FVector GetRight() const
	{
		return Right;
	}
	FVector GetFront() const
	{
		return Front;
	}
	FVector GetPosition() const
	{
		return Position;
	}

	FVector GetRotation() const
	{
		FVector rotation = {Yaw,Pitch,0.0f};
		return rotation;
	}

	void SetPosition(const FVector& pos)
	{
		Position = pos;
	}
	void SetRotation(const FVector& rot)
	{
		Yaw = rot.X;
		Pitch = rot.Y;
	}
private:
	//bool BMouseUpStart;
	bool BEnableMouseDownStart;

	//float MouseDownStartNdcX;
	//float MouseDownStartNdcY;

	float PreMouseNdcX;
	float PreMouseNdcY;

	float MouseNdcX;
	float MouseNdcY;

	// Camera의 local 회전각도
	float Yaw; // y축
	float Pitch; // x축

	// 카메라가 바라보는 방향 기준에서 각 방향
	FVector Up;
	FVector Right;
	FVector Front;

	// 카메라 월드 위치
	FVector Position;

	float MoveSpeed;
};