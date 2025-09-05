#pragma once
#include <d3d11.h>
#include <windows.h>

#include "CScene.h"
#include "FVertex.h"

class CEngine
{
public:
	CEngine();
	~CEngine();
	bool Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	bool Run();

	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:

	bool InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	bool InitD3D();
	bool InitImGui();

	void UpdateGUI();
	void Update(float deltaTime);
	void Render();
	void Release();

	void CreateDeviceAndSwapChain(HWND hWindow);
	//void InitializeAndSetPipeline();
	void CreateFrameBuffer();
	void CreateRasterizerState();
	//void CreateConstantBuffer();
	void CreateShader();
	//void CreateTextureSampler();
	//void SetRenderingPipeline();

	// 테스트용 임시 함수들
	void CreateVertexBuffer(FVertex* vertices, UINT byteWidth)
	{
		// 2. Create a vertex buffer
		D3D11_BUFFER_DESC vertexbufferdesc = {};
		vertexbufferdesc.ByteWidth = byteWidth;
		vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE; // will never be updated 
		vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

		Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &VertexBuffer);
	}

	struct FConstants
	{
		FVector Offset;
		float Radius;
		//float Pad;
	};

	void CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC constantbufferdesc = {};
		constantbufferdesc.ByteWidth = sizeof(FConstants) + 0xf & 0xfffffff0; // ensure constant buffer size is multiple of 16 bytes(+가 먼저 계산됨)
		constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC; // will be updated from CPU every frame
		constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Device->CreateBuffer(&constantbufferdesc, nullptr, &ConstantBuffer);

	}

	void UpdateConstant(FVector Offset, float radius)
	{
		if (ConstantBuffer)
		{
			D3D11_MAPPED_SUBRESOURCE constantbufferMSR;

			DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR); // update constant buffer every frame
			FConstants* constants = (FConstants*)constantbufferMSR.pData;
			{
				constants->Offset = Offset;
				constants->Radius = radius;
			}
			DeviceContext->Unmap(ConstantBuffer, 0);
		}
	}


private:
	//bool m_bIsRunning;
	unsigned int Stride = 0;

	D3D11_VIEWPORT ViewportInfo;
	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };

	HWND HWnd;
	CScene* PCurrentScene;

	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;
	ID3D11RasterizerState* RasterizerState = nullptr;

	ID3D11InputLayout* SimpleInputLayout = nullptr;
	ID3D11VertexShader* SimpleVertexShader = nullptr;
	ID3D11PixelShader* SimplePixelShader = nullptr;

	//테스트용 임시
	ID3D11Buffer* ConstantBuffer = nullptr;
	ID3D11Buffer* VertexBuffer = nullptr;

	ID3D11Buffer* MVPBuffer = nullptr;
};
