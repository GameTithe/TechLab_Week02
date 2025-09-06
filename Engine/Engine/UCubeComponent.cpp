#pragma once
#include "UCubeComponent.h"
#include "CEngine.h"

//void UCubeComponent::Initialize()
//{
//
//}

UCubeComponent::UCubeComponent()
{
	VertexBuffer = GeometryVertexBufferManager::GetInstance().GetCubeVertexBuffer();
	NumVertices = GeometryVertexBufferManager::GetInstance().GetNumCubeVertices();

	// 상수 버퍼 생성
	D3DUtil::CreateCBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),&ConstantBuffer, GetModelMatrix(), sizeof(FMVPConstants));
}

void UCubeComponent::UpdateConstantBuffer(float deltaTime)
{
	// Write Model Matrix to Constant Buffer
	D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(), ConstantBuffer, GetModelMatrix());
}

void UCubeComponent::Render() 
{
	CEngine::gpCEngine->GetDeviceContext()->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	CEngine::gpCEngine->GetDeviceContext()->Draw(NumVertices, 0);
}
