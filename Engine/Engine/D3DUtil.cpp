#include "D3DUtil.h"
#include "CEngine.h"


void D3DUtil::CreateCBuffer(ID3D11Buffer** cBuffer,UINT size)
{
	D3D11_BUFFER_DESC constantbufferdesc = {};
	constantbufferdesc.ByteWidth = size + 0xf & 0xfffffff0; // ensure constant buffer size is multiple of 16 bytes(+가 먼저 계산됨)
	constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC; // will be updated from CPU every frame
	constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CEngine::gpCEngine->GetDevice()->CreateBuffer(&constantbufferdesc,nullptr,cBuffer);
}

void D3DUtil::CreateRasterizerState(ID3D11RasterizerState** rasterizerState,D3D11_RASTERIZER_DESC& desc)
{
	CEngine::gpCEngine->GetDevice()->CreateRasterizerState(&desc,rasterizerState);
}
void D3DUtil::CreateVertexBuffer(FVertex* vertices,ID3D11Buffer** vertexBuffer,UINT byteWidth)
{
	D3D11_BUFFER_DESC vertexbufferdesc = {};
	vertexbufferdesc.ByteWidth = byteWidth;
	vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE; // will never be updated 
	vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexbufferSRD = {vertices};

	CEngine::gpCEngine->GetDevice()->CreateBuffer(&vertexbufferdesc,&vertexbufferSRD,vertexBuffer);

}

void D3DUtil::CreateVSAndInputLayout(const wstring& filePath,ID3D11VertexShader** vs,ID3D11InputLayout** inputLayout)
{
	ID3DBlob* vsCSO;
	D3DCompileFromFile(filePath.c_str(),nullptr,nullptr,"mainVS","vs_5_0",0,0,&vsCSO,nullptr);
	CEngine::gpCEngine->GetDevice()->CreateVertexShader(vsCSO->GetBufferPointer(),vsCSO->GetBufferSize(),nullptr,vs);
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		/*{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }*/
	};
	CEngine::gpCEngine->GetDevice()->CreateInputLayout(layout,ARRAYSIZE(layout),
		vsCSO->GetBufferPointer(),vsCSO->GetBufferSize(),inputLayout);
	vsCSO->Release();
}
void D3DUtil::CreatePS(const wstring& filePath,ID3D11PixelShader** ps)
{
	ID3DBlob* psCSO;
	D3DCompileFromFile(filePath.c_str(),nullptr,nullptr,"mainPS","ps_5_0",0,0,&psCSO,nullptr);
	CEngine::gpCEngine->GetDevice()->CreatePixelShader(psCSO->GetBufferPointer(),psCSO->GetBufferSize(),nullptr,ps);
	psCSO->Release();
}