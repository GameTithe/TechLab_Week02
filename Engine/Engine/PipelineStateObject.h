#pragma once

#include "D3DUtil.h"

class CPipelineStateObject
{
public:
	CPipelineStateObject() {};
	void PSOSetting();
private:
	//������ �ϴ� ����
	ID3D11BlendState* BlendState;
	ID3D11DepthStencilState* DepthStencilState;
	ID3D11RasterizerState* RasterizerState;
	ID3D11InputLayout* Inputlayout;
	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;
	
};