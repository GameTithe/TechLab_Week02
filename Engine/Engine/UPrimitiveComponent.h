#pragma once
#include "USceneComponent.h"
#include "D3DUtil.h"
#include "FVertex.h"
#include "FConstant.h"
// 렌더링 기능이 포함된 컴포넌트
class UPrimitiveComponent : public USceneComponent
{
	
public:
	UPrimitiveComponent() {}
	virtual ~UPrimitiveComponent() {}

	virtual void Initialize() = 0;
	virtual void UpdateConstant(float deltaTime) = 0;
	virtual void Render() = 0;

	void SetPrimitive
protected:
	TArray<FVertex> Vertices;
	FMVPConstants MVPConstantData;
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* ConstantBuffer = nullptr;
}; 