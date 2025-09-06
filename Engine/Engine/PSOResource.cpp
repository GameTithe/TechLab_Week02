
#include "PSOResource.h"

namespace PSO
{
ID3D11RasterizerState* RasterizerState = nullptr;
ID3D11InputLayout* SimpleInputLayout= nullptr;
ID3D11VertexShader* SimpleVS= nullptr;

ID3D11PixelShader* SimplePS= nullptr;
ID3D11PixelShader* MousePickingPS= nullptr;

CPipelineStateObject* SimplePSO = nullptr;
CPipelineStateObject* MousePickingPSO= nullptr;


void InitRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_BACK;
	desc.FillMode = D3D11_FILL_SOLID;
	D3DUtil::CreateRasterizerState(&RasterizerState, desc);
}
void InitShader()
{
	D3DUtil::CreateVSAndInputLayout(L"ShaderW0.hlsl",&SimpleVS,&SimpleInputLayout);
	D3DUtil::CreatePS(L"ShaderW0.hlsl",&SimplePS);
	D3DUtil::CreatePS(L"PickingPS.hlsl",&MousePickingPS);
}
void InitPSO()
{
	SimplePSO = new CPipelineStateObject();
	SimplePSO->RasterizerState = RasterizerState;
	SimplePSO->Inputlayout = SimpleInputLayout;
	SimplePSO->VS = SimpleVS;
	SimplePSO->PS = SimplePS;

	MousePickingPSO = new CPipelineStateObject();
	MousePickingPSO->RasterizerState = RasterizerState;
	MousePickingPSO->Inputlayout = SimpleInputLayout;
	MousePickingPSO->VS = SimpleVS;
	MousePickingPSO->PS = MousePickingPS;
}
void InitPSOResource()
{
	InitRasterizerState();
	InitShader();
	InitPSO();
}
void ReleasePSOResource()
{
	RasterizerState->Release();
	SimpleInputLayout->Release();
	SimpleVS->Release();

	SimplePS->Release();
	MousePickingPS->Release();

	delete SimplePSO;
	delete MousePickingPSO;

}
}
