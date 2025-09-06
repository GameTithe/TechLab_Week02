#pragma once
#include "USceneComponent.h"
#include "D3DUtil.h"
#include "FVertex.h"
#include "FConstant.h"
#include "CEngine.h"
// 렌더링 기능이 포함된 컴포넌트
class UPrimitiveComponent : public USceneComponent
{
public:
	UPrimitiveComponent() = default;
	virtual ~UPrimitiveComponent() 
	{
		if(ConstantBuffer)
		{
			ConstantBuffer->Release();
			ConstantBuffer = nullptr;
		}
	}

	/*virtual void Initialize() = 0;*/
	virtual void UpdateConstantBuffer(float deltaTime) = 0;
	virtual void Render() = 0;

protected:
	// ======= 공유 데이터 (GeometryVetexBufferManager로부터 포인터를 받아옴) =======
	ID3D11Buffer* VertexBuffer = nullptr;
	int NumVertices;
	// ======= 인스턴스가 별도로 소유하는 개별 데이터 =======
	ID3D11Buffer* ConstantBuffer = nullptr;

}; 