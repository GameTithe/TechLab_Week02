#pragma once
#include "UPrimitiveComponent.h"
#include "GeometryVertexBufferManager.h"
class UCubeComponent: public UPrimitiveComponent
{
public:
	UCubeComponent();

	//void Initialize() override;
	void UpdateConstantBuffer() override;
	void Render() override;

private:
};