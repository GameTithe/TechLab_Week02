#pragma once
#include "UCubeComponent.h"
#include "CEngine.h"

//void UCubeComponent::Initialize()
//{
//
//}

UCubeComponent::UCubeComponent()
{
	// 
	VertexBuffer = GeometryVertexBufferManager::GetInstance().GetCubeVertexBuffer();
	//MVPConstantData = 
	//D3DUtil::CreateCBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),&ConstantBuffer,Con, sizeof(FMVPConstants));
}

void UCubeComponent::UpdateConstant(float deltaTime)
{
	//D3DUtil::CreateCBufferUpdate
}

void UCubeComponent::Render() 
{

}
