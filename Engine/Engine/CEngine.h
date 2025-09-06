#pragma once

#include <d3d11.h>
#include <windows.h>

#include "CScene.h"
#include "FVertex.h"

#include "FConstant.h"
#include "CSceneManager.h"
#include "PSOResource.h"

#define PICKING_CBUFFER 2

class CEngine
{
public:
	CEngine();
	~CEngine();

	bool Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	bool Run();

	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	ID3D11Device* GetDevice()
	{
		return Device;
	}
	ID3D11DeviceContext* GetDeviceContext()
	{
		return DeviceContext;
	}
	ID3D11Buffer* GetPickingCBuffer()
	{
		return PickingCBuffer;
	}
	UINT GetPickID()
	{
		return PickID;
	}
	//void AddLog(const char* fmt, ...)

private:

	bool InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	bool InitD3D();
	bool InitImGui();
	 
	void Load();
	void UpdateGUI();
	void Update(float deltaTime);
	void Render();
	void Release();

	void CreateDeviceAndSwapChain(HWND hWindow); 
	void CreateFrameBuffer(); 
	 
	//Picking
	void CreatePickTargets();
	//void CreateDepthBuffer();
	void CreatePickDepth();
	int RenderPickIDAndRead(int mouseX, int mouseY);
	 
	void CreateVertexBuffer(FVertex* vertices, ID3D11Buffer** buffer, UINT byteWidth)
	{
		// 2. Create a vertex buffer
		D3D11_BUFFER_DESC vertexbufferdesc = {};
		vertexbufferdesc.ByteWidth = byteWidth;
		vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE; // will never be updated 
		vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

		Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, buffer); 
	}  

private:
	//bool m_bIsRunning;
	unsigned int Stride = sizeof(FVertex);

	D3D11_VIEWPORT ViewportInfo;
	FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
	

	HWND HWnd;
	CScene* PCurrentScene;

	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Texture2D* FrameBuffer = nullptr;
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;
	ID3D11Texture2D* DepthStencilTex = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;

	ID3D11Buffer* CommonCBuffer = nullptr;

	//테스트용 임시
	ID3D11Buffer* CubeVertexBuffer = nullptr;
	ID3D11Buffer* QuadVertexBuffer = nullptr;

	//Picking Test
	//ID3D11Texture2D* DepthBuffer;
	//ID3D11DepthStencilView* DepthBufferDSV; 

	ID3D11Texture2D* PickingTex;
	ID3D11Texture2D* PickDepthTex;
	ID3D11Texture2D* PickingStagingTex;

	ID3D11RenderTargetView* PickingRTV;
	ID3D11ShaderResourceView* PickingSRV;
	ID3D11DepthStencilView* PickingDSV;

	ID3D11Buffer* PickingCBuffer = nullptr;
	CSceneManager* SceneManager;
	UINT PickID = 0;
	UPrimitiveComponent* PickedPrimitive = nullptr;
	uint32 PickedPrimitiveID = 0;

public:
	static CEngine* gpCEngine;


	//test 
	FVector CamPos;
	FVector CamRot;
private:
};
