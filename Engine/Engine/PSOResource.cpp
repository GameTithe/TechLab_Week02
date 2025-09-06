
#include "PSOResource.h"

namespace PSO
{
ID3D11DepthStencilState* SimpleDSS = nullptr;
ID3D11RasterizerState* RasterizerState = nullptr;
ID3D11InputLayout* SimpleInputLayout= nullptr;
ID3D11VertexShader* SimpleVS= nullptr;

ID3D11PixelShader* SimplePS= nullptr;
ID3D11PixelShader* PickingPS= nullptr;

CPipelineStateObject* SimplePSO = nullptr;
CPipelineStateObject* PickingPSO= nullptr;

void InitDSS()
{
	D3D11_DEPTH_STENCIL_DESC desc = {};
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.StencilEnable = false;
	D3DUtil::CreateDepthStencilState(&SimpleDSS,desc);
}
void InitRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_BACK;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
	D3DUtil::CreateRasterizerState(&RasterizerState, desc);
}
void InitShader()
{
	D3DUtil::CreateVSAndInputLayout(L"ShaderW0.hlsl",&SimpleVS,&SimpleInputLayout);
	D3DUtil::CreatePS(L"ShaderW0.hlsl",&SimplePS);
	D3DUtil::CreatePS(L"PickingPS.hlsl",&PickingPS);
}
void InitPSO()
{
	SimplePSO = new CPipelineStateObject();
	SimplePSO->RasterizerState = RasterizerState;
	SimplePSO->Inputlayout = SimpleInputLayout;
	SimplePSO->VS = SimpleVS;
	SimplePSO->PS = SimplePS;
	SimplePSO->DepthStencilState = SimpleDSS;

	PickingPSO = new CPipelineStateObject();
	PickingPSO->RasterizerState = RasterizerState;
	PickingPSO->Inputlayout = SimpleInputLayout;
	PickingPSO->VS = SimpleVS;
	PickingPSO->PS = PickingPS;
	PickingPSO->DepthStencilState = SimpleDSS;
}
void InitPSOResource()
{
	InitDSS();
	InitRasterizerState();
	InitShader();
	InitPSO();
}
void ReleasePSOResource()
{
	SimpleDSS->Release();

	RasterizerState->Release();
	SimpleInputLayout->Release();
	SimpleVS->Release();

	SimplePS->Release();
	PickingPS->Release();


	delete SimplePSO;
	delete PickingPSO;

}
}
