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
	FMatrix modelMat = GetModelMatrix();
	D3DUtil::CreateCBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),&ConstantBuffer, modelMat, sizeof(FMVPConstants));
}

void UCubeComponent::UpdateConstantBuffer()
{
	// Write Model Matrix to Constant Buffer
	FMatrix modelMat = GetModelMatrix();
	D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(), ConstantBuffer,modelMat);
}

void UCubeComponent::Render() 
{
	UINT stride = sizeof(FVertex);
	UINT offset = 0;
	CEngine::gpCEngine->GetDeviceContext()->IASetVertexBuffers(0,1, &VertexBuffer, &stride, &offset);
	CEngine::gpCEngine->GetDeviceContext()->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	CEngine::gpCEngine->GetDeviceContext()->Draw(NumVertices, 0);
}
