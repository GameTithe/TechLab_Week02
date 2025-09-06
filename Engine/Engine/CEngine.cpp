#define UE_LOG(fmt, ...) ConsoleWindow::GetInstance().AddLog(fmt, ##__VA_ARGS__)

#include "CEngine.h"
#include "ConsoleWindow.h"

#include <windows.h>

// D3D libraries
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")	

// D3D headers 
#include <d3d11.h>
#include <d3dcompiler.h>	

//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "imGui/imgui_impl_win32.h"

#include "FVertex.h"
#include "FVector.h"

//input
#include "InputManager.h"


//�׽�Ʈ��
FVertex triangle_vertices[] =
{
	{  {0.0f,  1.0f, 0.0f},  {1.0f, 0.0f, 0.0f, 1.0f} }, // Top vertex (red)
	{  {1.0f, -1.0f, 0.0f},  {0.0f, 1.0f, 0.0f, 1.0f} }, // Bottom-right vertex (green)
	{ {-1.0f, -1.0f, 0.0f},  {0.0f, 0.0f, 1.0f, 1.0f} }  // Bottom-left vertex (blue)
};

//TODO 
FVertex cube_vertices[] =
{
	// +X (Right, red)
	{ {+1, -1, -1}, {1,0,0,1} }, { {+1, +1, -1}, {1,0,0,1} }, { {+1, +1, +1}, {1,0,0,1} },
	{ {+1, -1, -1}, {1,0,0,1} }, { {+1, +1, +1}, {1,0,0,1} }, { {+1, -1, +1}, {1,0,0,1} },

	// -X (Left, green)
	{ {-1, -1, +1}, {0,1,0,1} }, { {-1, +1, +1}, {0,1,0,1} }, { {-1, +1, -1}, {0,1,0,1} },
	{ {-1, -1, +1}, {0,1,0,1} }, { {-1, +1, -1}, {0,1,0,1} }, { {-1, -1, -1}, {0,1,0,1} },

	// +Y (Top, blue)
	{ {-1, +1, -1}, {0,0,1,1} }, { {-1, +1, +1}, {0,0,1,1} }, { {+1, +1, +1}, {0,0,1,1} },
	{ {-1, +1, -1}, {0,0,1,1} }, { {+1, +1, +1}, {0,0,1,1} }, { {+1, +1, -1}, {0,0,1,1} },

	// -Y (Bottom, yellow)
	{ {-1, -1, +1}, {1,1,0,1} }, { {-1, -1, -1}, {1,1,0,1} }, { {+1, -1, -1}, {1,1,0,1} },
	{ {-1, -1, +1}, {1,1,0,1} }, { {+1, -1, -1}, {1,1,0,1} }, { {+1, -1, +1}, {1,1,0,1} },

	// +Z (Front, magenta)
	{ {-1, -1, +1}, {1,0,1,1} }, { {+1, -1, +1}, {1,0,1,1} }, { {+1, +1, +1}, {1,0,1,1} },
	{ {-1, -1, +1}, {1,0,1,1} }, { {+1, +1, +1}, {1,0,1,1} }, { {-1, +1, +1}, {1,0,1,1} },

	// -Z (Back, cyan)
	{ {+1, -1, -1}, {0,1,1,1} }, { {-1, -1, -1}, {0,1,1,1} }, { {-1, +1, -1}, {0,1,1,1} },
	{ {+1, -1, -1}, {0,1,1,1} }, { {-1, +1, -1}, {0,1,1,1} }, { {+1, +1, -1}, {0,1,1,1} },
};
 
// 정점 4개 (사각형)
FVertex quad_vertices[] =
{
	
	{{-1.0f,1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f}}, // Top-left (red)
	{{1.0f,1.0f,1.0f},{0.0f,1.0f,0.0f,1.0f}}, // Top-right (green)
	{{1.0f,-1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f}}, // Bottom-right (blue)

	{{1.0f,-1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f}}, // Bottom-right (blue)
	{{-1.0f,-1.0f,1.0f},{1.0f,1.0f,0.0f,1.0f}},  // Bottom-left (yellow)
	{{-1.0f,1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f}}, // Top-left (red)
};
////////////Have to move to Camera.h////////////

struct Ray
{
	FVector Origin ;
	FVector Dir;
};

Ray ScreenToRay(int mouseX,int mouseY,
				const FMatrix& InvView,const FMatrix& invProj,
				float viewportW,float viewportH)
{
	auto ndc = [&](float x,float y,float z)
	{
		float nx = 2.0f * (x / viewportW) - 1.0f;
		float ny = 1.0f - 2.0f * (y / viewportH);

		return FVector4(nx,ny,z,1.0f);
	};

	FVector4 pNear = ndc((float)mouseX, (float)mouseY, 0.0f);
	FVector4 pFar = ndc((float)mouseX,(float)mouseY,1.0f);

	auto Unproject = [&](FVector4 p)
	{
		FVector4 v = p *invProj;	v /= v.W;
		FVector4 w = v * InvView;	w /= w.W;
		return FVector(w.X,w.Y,w.Z);
	};

	FVector nearWS = Unproject(pNear);
	FVector farWS = Unproject(pFar);

	Ray r;
	r.Origin = nearWS;
	r.Dir = (farWS - nearWS);
	r.Dir.Normalize();
	
	return r; 
}

bool RayPlaneHit(const Ray& r,const FVector& p0,const FVector& N,FVector& outHit)
{
	// normal dot ( p - p )  
	float denom = N.Dot(r.Dir);
	
	if(abs(denom) < 1e-10) return false;
	
	float t = (p0 - r.Origin).Dot(N) / denom;
	if(t < 0.0f) return false;

	outHit = r.Origin + r.Dir * t;
	return true;
}
////////////////////////////////////////////////
 
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

CEngine* CEngine::gpCEngine = nullptr;
// ���� �޼����� ó���� �Լ�
//InputManager gInput = InputManager::Get();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return CEngine::gpCEngine->MsgProc(hWnd, message, wParam, lParam);
}

LRESULT CEngine::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}
	 
	InputManager::Get().ProcessMessage(message,wParam,lParam);
	
	switch (message)
	{
	case WM_DESTROY:
		// signal the the app should quit
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


CEngine::CEngine()
{
	//PCurrentScene = new CScene();
	gpCEngine = this;

	CameraComponent = UCameraComponent();
	//ConsoleWindow::GetInstance().AddLog("hi");
}

CEngine::~CEngine()
{
	gpCEngine = nullptr;

	//delete PCurrentScene;
	// ���⿡�� ImGui �Ҹ�
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	Release();
}

bool CEngine::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if(!InitWindow(hInstance, hPrevInstance, lpCmdLine, nShowCmd))
		return false;
	if (!InitD3D())
		return false;
	if (!InitImGui())
		return false;
	//PCurrentScene->Load();

	return true;
}
void CEngine::Load()
{
	D3DUtil::CreateCBuffer(&CommonCBuffer,sizeof(CommonConstantBuffer));
	SceneManager = new CSceneManager();
	PSO::InitPSOResource();
}

int PickTest = 0;

FVector modelPos;
FVector modelRot;
FVector modelScale = FVector(1,1,1);

void CEngine::UpdateGUI()
{
	//UE_LOG("%d",PickTest);

	ImGui::SliderFloat3("modelPos (x,y,z)",&modelPos.X,-4.0f,4.0f,"%.3f");
	ImGui::SliderFloat3("modelRot(x,y,z)",&modelRot.X,-180.0f,180.0f,"%.3f");
	ImGui::SliderFloat3("modelScale(x,y,z)",&modelScale.X,-4.0f,4.0f,"%.3f");
	if(ImGui::SliderFloat3("camPos (x,y,z)",&CamPos.X,-20.0f,20.0f))
	{
		CameraComponent.SetPosition(CamPos);
	}
	if(ImGui::SliderFloat3("camRot(x,y,z)",&CamRot.X,-360.0f,360.0f))
	{
		CameraComponent.SetRotation(CamRot);
	}

	CamPos = CameraComponent.GetPosition();
	CamRot = CameraComponent.GetRotation();

	SceneManager->GetScene().SceneActors[0]->GetRootComponent()->SetRelativeLocation(modelPos);
	SceneManager->GetScene().SceneActors[0]->GetRootComponent()->SetRelativeRotation(modelRot);
	SceneManager->GetScene().SceneActors[0]->GetRootComponent()->SetRelativeScale3D(modelScale);

	/*ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();*/
	// ImGui UI ��Ʈ�� �߰��� ImGui::NewFrame()�� ImGui::Render() ���̿�
	/*ImGui::Begin("Jungle Property Window");
	ImGui::Text("Hello Jungle World!");*/
	//ImGui TODO 
	/*ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());*/
}

//void CEngine::Update(float deltaTime)
//{
//	//PCurrentScene->Store();
//	//PCurrentScene->Load();
//}
//
//void CEngine::Render()
//{
//	//renderer.DeviceContext->ClearRenderTargetView(renderer.RenderTargetView, ClearColor);
//	//renderer.DeviceContext->ClearDepthStencilView(renderer.DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
//	//PCurrentScene->Render();
//	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
//	//renderer.SwapChain->Present(0, 0);
//}

bool CEngine::Run()
{
	//UE_LOG("hi");

	bool bIsExit = false;
	Load();
	// Main Loop 
	while (bIsExit == false)
	{

		MSG msg;

		//�޽��� ť���� msg�� �������� ť���� ������ 
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			/*float mouseX = gInput.GetX();
			float mouseY = gInput.GetY();
			UE_LOG("%.2f, %.2f",mouseX,mouseY);*/

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		} 
		Update(ImGui::GetIO().DeltaTime); // Update

		//PickTest = RenderPickIDAndRead(gInput.GetX(),gInput.GetY());
		ImGuiIO& io = ImGui::GetIO();
		ImVec2 mousePos = io.MousePos;
		//UE_LOG("%.2f %.2f",mousePos.x ,mousePos.y);

		//PickTest = RenderPickIDAndRead(mousePos.x,mousePos.y);
		Render(); // Render

		//basic movement  

		// ImGui Update
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// ImGui UI ��Ʈ�� �߰��� ImGui::NewFrame()�� ImGui::Render() ���̿�
		ImGui::Begin("Jungle Property Window");
		ImGui::Text("Hello Jungle World!");

		UpdateGUI(); // �߰������� ����� GUI

        bool bConsoleDraw = true;
		ConsoleWindow::GetInstance().Draw("Example: Console", &bConsoleDraw);

		ImGui::End(); 
		ImGui::Render();

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		SwapChain->Present(1, 0); // ȭ�� ǥ��
	}

	return true;
}

//void CEngine::AddLog(const char* fmt, ...)
//{
//	PConsoleWindow->AddLog(fmt);
//}

bool CEngine::InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// ������ Ŭ���� �̸�
	WCHAR WindowClass[] = L"JungleWindowClass";

	// ������ Ÿ��Ʋ�� �̸�
	WCHAR Title[] = L"Game Tech Lab";

	// ���� �޼����� ó���� �Լ��� WndProc�� �Լ� �����͸� WindowClass ����ü�� ���
	WNDCLASSW wndClass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

	// ������ Ŭ���� ���
	RegisterClassW(&wndClass);

	DWORD style = WS_OVERLAPPEDWINDOW;   // 보더/타이틀 유지
	DWORD ex    = 0;

	RECT rc = {0,0,1024,1024};             // 원하는 "클라이언트" 크기
	AdjustWindowRectEx(&rc,style,FALSE,ex);  // 외곽 크기로 보정
	int W = rc.right - rc.left;
	int H = rc.bottom - rc.top;

	HWnd = CreateWindowExW(
		ex,WindowClass,Title,style | WS_VISIBLE,
		CW_USEDEFAULT,CW_USEDEFAULT,W,H,
		nullptr,nullptr,hInstance,nullptr);
	 
	return true;
}

bool CEngine::InitD3D()
{
	// DeviceAndSwapChain
	CreateDeviceAndSwapChain(HWnd);

	CreateFrameBuffer();

	// �׽�Ʈ�� �ӽ�
	CreateConstantBuffer();
	//CreateVertexBuffer(triangle_vertices, sizeof(triangle_vertices));
	CreateVertexBuffer(cube_vertices, &CubeVertexBuffer, sizeof(cube_vertices));
	CreateVertexBuffer(quad_vertices, &QuadVertexBuffer, sizeof(quad_vertices));

	//Depth Buffer
	CreateDepthBuffer();

	//Picking Setting
	CreatePickTargets();
	CreatePickDepth();

	return true;
}

bool CEngine::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(HWnd);
	ImGui_ImplDX11_Init(Device, DeviceContext);

	return true;
}

void CEngine::CreateDeviceAndSwapChain(HWND hWindow)
{
	// �����ϴ� Direct3D ��� ������ ����
	D3D_FEATURE_LEVEL featurelevels[] = { D3D_FEATURE_LEVEL_11_0 };

	// ���� ü�� ���� ����ü �ʱ�ȭ
	DXGI_SWAP_CHAIN_DESC swapchaindesc = {};
	swapchaindesc.BufferDesc.Width = 0; // â ũ�⿡ �°� �ڵ����� ����
	swapchaindesc.BufferDesc.Height = 0; // â ũ�⿡ �°� �ڵ����� ����
	swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // ���� ����
	swapchaindesc.SampleDesc.Count = 1; // ��Ƽ ���ø� ��Ȱ��ȭ
	swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� Ÿ������ ���
	swapchaindesc.BufferCount = 2; // ���� ���۸�
	swapchaindesc.OutputWindow = hWindow; // �������� â �ڵ�
	swapchaindesc.Windowed = TRUE; // â ���
	swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ���� ���

	// Direct3D ��ġ�� ���� ü���� ����
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
		featurelevels, ARRAYSIZE(featurelevels), D3D11_SDK_VERSION,
		&swapchaindesc, &SwapChain, &Device, nullptr, &DeviceContext);

	// ������ ���� ü���� ���� ��������
	SwapChain->GetDesc(&swapchaindesc);

	// ����Ʈ ���� ����
	ViewportInfo = { 0.0f, 0.0f, (float)swapchaindesc.BufferDesc.Width, (float)swapchaindesc.BufferDesc.Height, 0.0f, 1.0f };
}

void CEngine::CreateFrameBuffer()
{
	// ���� ü�����κ��� �� ���� �ؽ�ó ��������
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);

	// ���� Ÿ�� �� ����
	D3D11_RENDER_TARGET_VIEW_DESC framebufferRTVdesc = {};
	framebufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // ���� ����
	framebufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D �ؽ�ó

	Device->CreateRenderTargetView(FrameBuffer, &framebufferRTVdesc, &FrameBufferRTV);

	D3D11_TEXTURE2D_DESC frameBufferDesc = {};
	FrameBuffer->GetDesc(&frameBufferDesc);



	D3D11_TEXTURE2D_DESC depthTex = {};
	depthTex.Width =	frameBufferDesc.Width;
	depthTex.Height = frameBufferDesc.Height;
	depthTex.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTex.Usage = D3D11_USAGE_DEFAULT;
	depthTex.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTex.MipLevels = 1;
	depthTex.ArraySize = 1;
	depthTex.SampleDesc.Count = 1;
	depthTex.SampleDesc.Quality = 0;
	HRESULT hResult = Device->CreateTexture2D(&depthTex,nullptr,&DepthStencilTex);
	if(FAILED(hResult))
	{
		int a=0;
		return;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc ={};
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	hResult =Device->CreateDepthStencilView(DepthStencilTex,&depthStencilViewDesc,&DepthStencilView);
	if(FAILED(hResult))
	{
		int a=0;
		return;
	}
}

void CEngine::CreatePickTargets()
{
	//write용 texture
	D3D11_TEXTURE2D_DESC td{};
	td.Width = (UINT)ViewportInfo.Width;
	td.Height = (UINT)ViewportInfo.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R32_UINT;
	td.SampleDesc.Count = 1; // MUST OFF MSAA
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; 
	Device->CreateTexture2D(&td, nullptr, &PickIDTex);

	// read용 texture 
	td.BindFlags = 0;
	td.Usage = D3D11_USAGE_STAGING;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	Device->CreateTexture2D(&td, nullptr, &PickID_Staging);

	// RTV
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.Format = td.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	Device->CreateRenderTargetView(PickIDTex, &rtvDesc, &PickID_RTV);

	// SRV
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = td.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	Device->CreateShaderResourceView(PickIDTex, &srvDesc, &PickID_SRV);
	 
}

void CEngine::CreateDepthBuffer()
{
	D3D11_TEXTURE2D_DESC depthDesc = {};
	depthDesc.Width = (UINT)ViewportInfo.Width;
	depthDesc.Height = (UINT)ViewportInfo.Height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	Device->CreateTexture2D(&depthDesc,nullptr,&DepthBuffer);

	// 깊이 스텐실 뷰 생성
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = depthDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	Device->CreateDepthStencilView(DepthBuffer,&dsvDesc,&DepthBufferDSV);


}

void CEngine::CreatePickDepth()
{
	D3D11_TEXTURE2D_DESC td{};
	td.Width = (UINT)ViewportInfo.Width;
	td.Height = (UINT)ViewportInfo.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	Device->CreateTexture2D(&td, nullptr, &PickDepthTex);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = td.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	Device->CreateDepthStencilView(PickDepthTex, &dsvDesc, &PickDepth_DSV);	
}

int CEngine::RenderPickIDAndRead(int mouseX, int mouseY)
{
	// 상태 백업
	ID3D11RenderTargetView* oldRTV = nullptr;
	ID3D11DepthStencilView* oldDSV = nullptr;
	DeviceContext->OMGetRenderTargets(1, &oldRTV, &oldDSV);

	// clear
	float clearID[4] = { 0, 0 ,0 , 0 };
	DeviceContext->OMSetRenderTargets(1, &PickID_RTV, PickDepth_DSV); 
	DeviceContext->ClearRenderTargetView(PickID_RTV, clearID);
	DeviceContext->ClearDepthStencilView(PickDepth_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//picking pipeline 
	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
	/*DeviceContext->IASetInputLayout(SimpleInputLayout);
	DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);
	DeviceContext->PSSetShader(PickID_PixelShader, nullptr, 0);*/

	// Draw All Actors For Picking
	for(int i = 1; i <= 2; i++)
	{
		D3D11_MAPPED_SUBRESOURCE pickBufferMSR{};
		DeviceContext->Map(PickID_CB, 0, D3D11_MAP_WRITE_DISCARD, 0, &pickBufferMSR);
		
		FObjectPicking* pickConst = (FObjectPicking*)pickBufferMSR.pData;
		{
			pickConst->Pick = 0.0;
			pickConst->ObjectID = i; 
		}
		DeviceContext->Unmap(PickID_CB, 0);

		DeviceContext->PSSetConstantBuffers(0, 1, &PickID_CB);

		//// 동일한 VS 상수(MVP) 바인딩
		//if (ConstantBuffer && MVPConstantBuffer)
		//{
		//	DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
		//	DeviceContext->VSSetConstantBuffers(1, 1, &MVPConstantBuffer);
		//}

		UINT offset = 0; 
		UINT numVertices = 0;
	/*	switch(i)
		{
		case 1:
		{
			UpdateConstant({0.0f,0.0f,0.0f},1.0f,camPosTest,modelPosTest,modelRotTest,PickTest,i);
			DeviceContext->IASetVertexBuffers(0,1,&CubeVertexBuffer,&Stride,&offset);
			numVertices = sizeof(cube_vertices) / sizeof(FVertex);
		}break;
		case 2:
		{
			UpdateConstant({0.0f,0.0f,0.0f},1.0f,camPosTest,FVector(0.5,0.0,0.0),FVector(0,0,0),PickTest,i);

			DeviceContext->IASetVertexBuffers(0,1,&QuadVertexBuffer, &Stride,&offset);
			numVertices = sizeof(quad_vertices) / sizeof(FVertex);
		}
		}*/
		 
		DeviceContext->Draw(numVertices, 0);
	}

	mouseX = mouseX < 0 ? 0 : mouseX;
	mouseY = mouseY < 0 ?  0 : mouseY;

	mouseX = mouseX > 1023 ?  1000 : mouseX;
	mouseY = mouseY > 1023 ?  1000 : mouseY;

    // 5) 1×1만 스테이징으로 복사 → Map
    D3D11_BOX box{};
    box.left   = (UINT)mouseX;
    box.top    = (UINT)mouseY;
    box.front  = 0;
    box.right  = box.left + 1;
    box.bottom = box.top  + 1;
    box.back   = 1;

    DeviceContext->CopySubresourceRegion(PickID_Staging, 0, 0, 0, 0, PickIDTex, 0, &box);

    D3D11_MAPPED_SUBRESOURCE mapped{};
    DeviceContext->Map(PickID_Staging, 0, D3D11_MAP_READ, 0, &mapped);
    // 행 pitch 고려: 1픽셀만 읽으므로 첫 DWORD
    int picked = *(int*)mapped.pData;
    DeviceContext->Unmap(PickID_Staging, 0);

    // 6) 상태 복원
    DeviceContext->OMSetRenderTargets(1, &oldRTV, oldDSV);
    if (oldRTV) oldRTV->Release();
    if (oldDSV) oldDSV->Release();

    return picked; // 0 == 히트 없음 
}

void CEngine::Update(float deltaTime)
{
 
}

void CEngine::Render()
{
	//회전 순서 : z * y * x
	
	//CommonConstantBuffer
	CommonConstantBuffer commonCBufferData; 
	DeviceContext->ClearRenderTargetView(FrameBufferRTV,ClearColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView,D3D11_CLEAR_DEPTH,1.0f,0);

	/*FVector eye = FVector(0,0,-10);
	FVector at = FVector::FRONT;
	FVector up = {0.0f,1.0f,0.0f};*/

	float mouseX = InputManager::Get().GetX();
	float mouseY = InputManager::Get().GetY();
	//UE_LOG("%.2f, %.2f",mouseX,mouseY);
	CameraComponent.UpdateAngleAndDirection(mouseX,mouseY,ViewportInfo.Width,ViewportInfo.Height);
	/*if(InputManager::Get().IsDown(MouseButton::Right))
	{
		CameraComponent.UpdateAngleAndDirection(mouseX,mouseY,ViewportInfo.Width,ViewportInfo.Height);
	}*/
	CameraComponent.UpdatePosition();

	FVector eye = CameraComponent.GetPosition();
	FVector at = CameraComponent.GetFront();
	FVector up = CameraComponent.GetUp();

	//UE_LOG("eye: (%f, %f, %f)",eye.X,eye.Y,eye.Z);
	UE_LOG("at: (%f, %f, %f)",at.X,at.Y,at.Z);
	commonCBufferData.View = FMatrix::MakeLookAt(eye, at, up);
	//commonCBufferData.View.Transpose();

	commonCBufferData.Perspective = FMatrix::MakePerspectiveMatrix(30.0f,1.0f,0.1f,100.0f);
	//commonCBufferData.Perspective.Transpose();

	D3DUtil::CBufferUpdate(DeviceContext,CommonCBuffer,commonCBufferData);
	DeviceContext->VSSetConstantBuffers(1,1,&CommonCBuffer);

	DeviceContext->OMSetRenderTargets(1,&FrameBufferRTV,DepthStencilView);
	
	// IA
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->RSSetViewports(1,&ViewportInfo);

	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0,1,&CubeVertexBuffer,&Stride,&offset);
	SceneManager->GetScene().RenderScene();
	 
	//if (ConstantBuffer && MVPConstantBuffer)
	//{
	//	DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer); 
	//	DeviceContext->PSSetConstantBuffers(0, 1, &ConstantBuffer); 

	//	DeviceContext->VSSetConstantBuffers(1, 1, &MVPConstantBuffer);
	//	
	//	DeviceContext->PSSetConstantBuffers(2, 1, &PickID_CB);
	//	
	//}
	//UINT numVertices = 0;
	//for(int i = 1; i <= 2; i++)
	//{ 
	//	UINT offset = 0;
	//	switch(i)
	//	{
	//	case 1:
	//	{
	//		UpdateConstant({0.0f,0.0f,0.0f},1.0f,camPosTest,modelPosTest,modelRotTest,PickTest, i);

	//UpdateConstant({ 0.0f, 0.0f, 0.0f }, 1.0f , camPosTest, modelPosTest, modelRotTest, PickTest);

	//		const UINT numVertices = sizeof(triangle_vertices) / sizeof(FVertex); //
	//		numVertices = sizeof(cube_vertices) / sizeof(FVertex); //  
	//		 
	//	}break;
	//	case 2:
	//	{
	//		UpdateConstant({0.0f,0.0f,0.0f},1.0f,camPosTest,FVector(0.5, 0.0, 0.0),FVector(0,0,0),PickTest, i);

	//		DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &offset);
	//		DeviceContext->IASetVertexBuffers(0,1,&QuadVertexBuffer,&Stride,&offset); 
	//		const UINT numVertices = sizeof(triangle_vertices) / sizeof(FVertex); // 
	//		 numVertices = sizeof(quad_vertices) / sizeof(FVertex); //
	//	}
	//	break;
	//	}


	//	DeviceContext->Draw(numVertices,0);

	//}
}

void CEngine::Release()
{
	PSO::ReleasePSOResource();
	DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	if (FrameBuffer)
	{
		FrameBuffer->Release();
		FrameBuffer = nullptr;
	}
	if (FrameBufferRTV)
	{
		FrameBufferRTV->Release();
		FrameBufferRTV = nullptr;
	}

	if (DeviceContext)
	{
		DeviceContext->Flush(); // �����ִ� GPU ���� ����
	}

	if (SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}

	if (DeviceContext)
	{
		DeviceContext->Release();
		DeviceContext = nullptr;
	}

	
	/*PickID_SRV);
	PickID_RTV);
	PickIDTex);
	PickID_Staging);
	PickDepth_DSV);
	PickDepthTex);
	PickID_PixelShader);
	PickID_CB);

	DepthByuffERDSV
	DepthBuffer
	*/
	
}