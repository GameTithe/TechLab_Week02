#pragma once

#include "Log.h"
#include "UCameraComponent.h"
//#include "CEngine.h"
#include "InputManager.h"

#include <algorithm>
#include <DirectXMath.h>

UCameraComponent::UCameraComponent()
{
	Up = FVector::UP;
	Front = FVector::FRONT;
	Right = FVector::RIGHT;

	Yaw = 0.0f;
	Pitch = 0.0f;

	Position = {0.0f,0.0f,-10.0f};
	MoveSpeed = 0.2f;
}

void UCameraComponent::UpdateAngleAndDirection(int mouseX,int mouseY, float screenWidth, float screenHeight)
{
	if(!InputManager::Get().IsDown(MouseButton::Right))
	{
		BEnableMouseDownStart = true;
		return;
	}

	if(BEnableMouseDownStart)
	{
		BEnableMouseDownStart = false;
		
		PreMouseNdcX = mouseX * 2.0f / screenWidth - 1.0f;
		PreMouseNdcY = -mouseY * 2.0f / screenWidth + 1.0f;
	}

	MouseNdcX = mouseX * 2.0f / screenWidth - 1.0f;
	MouseNdcY = -mouseY * 2.0f / screenWidth + 1.0f;

	if(MouseNdcX < -1.0f)
	{
		MouseNdcX = -1.0;
	}
	else if(MouseNdcX > 1.0f)
	{
		MouseNdcX = 1.0;
	}

	if(MouseNdcY < -1.0f)
	{
		MouseNdcY = -1.0;
	} 
	else if(MouseNdcY > 1.0f)
	{
		MouseNdcY = 1.0;
	}

	//UE_LOG("MouseNdcX: %.2f, MouseNdcY: %.2f",MouseNdcX, MouseNdcY);

	/*Yaw = MouseNdcX * DirectX::XM_2PI;
	Pitch = MouseNdcY * DirectX::XM_PIDIV2;*/

	const float MouseNdcXDelta = MouseNdcX - PreMouseNdcX;
	const float MouseNdcYDelta = MouseNdcY - PreMouseNdcY;

	const float YawDelta = MouseNdcXDelta * 360.0f;
	const float PitchDelta = MouseNdcYDelta * 90.0f;
	//UE_LOG("YawDelta: %.2f, PitchDelta: %.2f",YawDelta,PitchDelta);

	Yaw += YawDelta;
	Pitch += PitchDelta;

	/*Yaw = MouseNdcX * 360.0f;
	Pitch = MouseNdcY * 90.0f;*/
	//UE_LOG("yaw: %.2f, pitch: %.2f",Yaw,Pitch);

	FMatrix rotationYMTranspose = FMatrix::MakeRotationYMatrix(Yaw);
	//rotationYMTranspose.Transpose();

	FMatrix rotationXMTranspose = FMatrix::MakeRotationXMatrix(Pitch);
	rotationXMTranspose.Transpose(); // -z방향 바라보면 반대로 회전함

	const FVector4 front4OnlyYawRoation = FVector4::FRONT * rotationYMTranspose;
	const FVector4 Front4 = front4OnlyYawRoation * rotationXMTranspose;
	Front = Front4.ToFVector();

	Right = Up.Cross(Front);

	PreMouseNdcX = MouseNdcX;
	PreMouseNdcY = MouseNdcY;

	//Up은 그냥 FVector::UP로 고정

	//todo: 아직 할거 남음
}

void UCameraComponent::UpdatePosition()
{
	if(InputManager::Get().IsKeyDown(KeyButton::W))
	{
		Position += MoveSpeed * Front;
	}
	if(InputManager::Get().IsKeyDown(KeyButton::A))
	{
		Position += MoveSpeed * Right * -1.0f;
	}
	if(InputManager::Get().IsKeyDown(KeyButton::S))
	{
		Position += MoveSpeed * Front * -1.0f;
	}
	if(InputManager::Get().IsKeyDown(KeyButton::D))
	{
		Position += MoveSpeed * Right;
	}
}
