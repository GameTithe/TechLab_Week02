#pragma once

#include "Camera.h"

#include <algorithm>

void CameraComponent::UpdateAngleAndDirection(int mouseX,int mouseY, float screenWidth, float screenHeight)
{
	MouseNdcX = mouseX * 2.0f / screenWidth - 1.0f;
	MouseNdcY = mouseY * 2.0f / screenWidth - 1.0f;

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

	//Yaw = mouseNdcX * DirectX::

	//todo: 아직 할거 남음
}
