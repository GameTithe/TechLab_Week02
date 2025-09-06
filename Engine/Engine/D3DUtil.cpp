#include "D3DUtil.h"
#include "CEngine.h"

void D3DUtil::CreateRasterizerState(ID3D11RasterizerState** rasterizerState, D3D11_RASTERIZER_DESC& desc)
{
	CEngine::gpCEngine->GetDevice()->CreateRasterizerState(&desc,rasterizerState);
}
void D3DUtil::CreateCBuffer(ID3D11Buffer** cBuffer, UINT size)
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = size;
	CEngine::gpCEngine->GetDevice()->CreateBuffer()
}
void D3DUtil::CreateVertexBuffer(ID3D11Buffer** vertexBuffer)
{

}
void D3DUtil::CreateIndexBuffer(ID3D11Buffer** indexBuffer)
{

}
void D3DUtil::CreateVSAndInputLayout(const wstring& filePath,ID3D11VertexShader** vs,ID3D11InputLayout** inputLayout,D3D11_INPUT_ELEMENT_DESC& inputLayoutDesc)
{

}
void D3DUtil::CreatePS(const wstring& filePath,ID3D11PixelShader** ps)
{

}