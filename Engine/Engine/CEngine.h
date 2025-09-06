#pragma once

#include <d3d11.h>
#include <windows.h>

#include "CScene.h"
#include "FVertex.h"

#include "FConstant.h"
#include "CSceneManager.h"

class CEngine
{
public:
	CEngine();
	~CEngine();
	CSceneManager* SceneManager;

	bool Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	bool Run();

	LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//void AddLog(const char* fmt, ...);
public:
	//test 
	static CEngine* gpCEngine;

	FVector CamPos;
	FVector CamRot;

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
	//void InitializeAndSetPipeline();
	void CreateFrameBuffer();
	void CreateRasterizerState();
	//void CreateConstantBuffer();
	void CreateShader();
	//void CreateTextureSampler();
	//void SetRenderingPipeline();

	//Picking
	void CreatePickTargets();
	void CreatePickDepth();
	int RenderPickIDAndRead(int mouseX, int mouseY);

	// �׽�Ʈ�� �ӽ� �Լ���
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
	 
	void CreateConstantBuffer()
	{
		//const Offset Scale
		D3D11_BUFFER_DESC constantbufferdesc = {};
		constantbufferdesc.ByteWidth = sizeof(FConstants) + 0xf & 0xfffffff0; // ensure constant buffer size is multiple of 16 bytes(+가 먼저 계산됨)
		constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC; // will be updated from CPU every frame
		constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Device->CreateBuffer(&constantbufferdesc, nullptr, &ConstantBuffer);

		//const MVP
		D3D11_BUFFER_DESC ConstantMVPBufferDesc = {};
		ConstantMVPBufferDesc.ByteWidth = sizeof(FMVPConstants) + 0xf & 0xfffffff0; // ensure constant buffer size is multiple of 16 bytes(+가 먼저 계산됨)
		ConstantMVPBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // will be updated from CPU every frame
		ConstantMVPBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ConstantMVPBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Device->CreateBuffer(&ConstantMVPBufferDesc, nullptr, &MVPConstantBuffer); 

		//Picking 
		D3D11_BUFFER_DESC pickingBufferDesc{};
		pickingBufferDesc.ByteWidth = 16;
		pickingBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		pickingBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		pickingBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Device->CreateBuffer(&pickingBufferDesc, nullptr, &PickID_CB);
	}

	void UpdateConstant(FVector Offset, float radius, FVector cam, FVector model, FVector rot, int PickTest)
	{
		if (ConstantBuffer && MVPConstantBuffer)
		{
			D3D11_MAPPED_SUBRESOURCE constantbufferMSR;

			DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR); // update constant buffer every frame
			FConstants* constants = (FConstants*)constantbufferMSR.pData;
			{
				constants->Offset = Offset;
				constants->Radius = radius; 
			}
			DeviceContext->Unmap(ConstantBuffer, 0);


			D3D11_MAPPED_SUBRESOURCE mvpConstantBufferMSR;
			DeviceContext->Map(MVPConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mvpConstantBufferMSR); // update constant buffer every frame
			FMVPConstants* mvpConstants = (FMVPConstants*)mvpConstantBufferMSR.pData;
			{
				FVector4 offset = { model.X, model.Y , model.Z , 0.0f };
				FMatrix Scale = FMatrix::MakeScaleMatrix(0.2);
				FMatrix Rotation = FMatrix::MakeRotationZMatrix(rot.Z)* FMatrix::MakeRotationYMatrix(rot.Y)* FMatrix::MakeRotationXMatrix(rot.X);
				FMatrix Translation = FMatrix::MakeTranslationMatrix(offset);

				mvpConstants->Model = Scale * Rotation * Translation ;

				FVector camPos = { cam.X, cam.Y, cam.Z};
				FVector at = FVector::FRONT; 
				FVector up = { 0.0f, 1.0f, 0.0f };

				mvpConstants->View = FMatrix::MakeLookAt(camPos, at, up); 

				FMatrix perspect = FMatrix::MakePerspectiveMatrix(30.0f, 1.0f, 0.1f, 100.0f);
				mvpConstants->Perspective = perspect;
				 
			} 
			DeviceContext->Unmap(MVPConstantBuffer,0);

			D3D11_MAPPED_SUBRESOURCE pickBufferMSR{};
			DeviceContext->Map(PickID_CB,0,D3D11_MAP_WRITE_DISCARD,0,&pickBufferMSR); 
			FObjectPicking* pickConst = (FObjectPicking*)pickBufferMSR.pData;
			{
				pickConst->Pick = PickTest;
				pickConst->ObjectID = 1;
			}
			DeviceContext->Unmap(PickID_CB,0);


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
	ID3D11PixelShader* PickID_PixelShader = nullptr;

	//테스트용 임시
	ID3D11Buffer* ConstantBuffer = nullptr;
	ID3D11Buffer* MVPConstantBuffer = nullptr;

	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* CubeVertexBuffer = nullptr;

	ID3D11Buffer* MVPBuffer = nullptr;

	//Picking Test
	ID3D11Texture2D* PickIDTex;
	ID3D11Texture2D* PickDepthTex;
	ID3D11Texture2D* PickID_Staging;

	ID3D11RenderTargetView* PickID_RTV;
	ID3D11ShaderResourceView* PickID_SRV;
	ID3D11DepthStencilView* PickDepth_DSV;

	ID3D11Buffer* PickID_CB = nullptr;
};
