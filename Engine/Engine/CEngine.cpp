#include "ConsoleWindow.h"
#include "CEngine.h"

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

//�׽�Ʈ��
FVertex triangle_vertices[] =
{
	{  {0.0f,  1.0f, 0.0f},  {1.0f, 0.0f, 0.0f, 1.0f} }, // Top vertex (red)
	{  {1.0f, -1.0f, 0.0f},  {0.0f, 1.0f, 0.0f, 1.0f} }, // Bottom-right vertex (green)
	{ {-1.0f, -1.0f, 0.0f},  {0.0f, 0.0f, 1.0f, 1.0f} }  // Bottom-left vertex (blue)
};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

CEngine* gpCEngine = nullptr;
// ���� �޼����� ó���� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return gpCEngine->MsgProc(hWnd, message, wParam, lParam);
}

LRESULT CEngine::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}

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

FVector modelTest(0.0f, 0.0f, -1.0f);
//FVector camRotTest(0.0f, 0.0f, -1.0f);
float modelRotTest= 0.0f;
void CEngine::UpdateGUI()
{
	bool changed = ImGui::SliderFloat3("Model Pos (x,y,z)", &modelTest.X, -4.0f, 4.0f, "%.3f");
	bool changed2= ImGui::SliderFloat3("Model Rotation (x,y,z)", &modelRotTest, -180.0f, 180.0f, "%.3f");


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
	bool bIsExit = false;

	// Main Loop 
	while (bIsExit == false)
	{

		MSG msg;

		//�޽��� ť���� msg�� �������� ť���� ������ 
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		} 
		Update(ImGui::GetIO().DeltaTime); // Update


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

		ImGui::End();

        bool bConsoleDraw = true;
        ShowExampleAppConsole(&bConsoleDraw);

		ImGui::Render();

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		SwapChain->Present(1, 0); // ȭ�� ǥ��
	}

	return true;
}

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

	// 1024 * 1024 ũ���� ������ ����
	HWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024, nullptr, nullptr, hInstance, nullptr);

	return true;
}

bool CEngine::InitD3D()
{
	// DeviceAndSwapChain
	CreateDeviceAndSwapChain(HWnd);

	CreateFrameBuffer();

	CreateRasterizerState();

	// vs, ps, InputLayout ����
	CreateShader();

	// �׽�Ʈ�� �ӽ�
	CreateConstantBuffer();
	CreateVertexBuffer(triangle_vertices, sizeof(triangle_vertices));

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
}

void CEngine::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerdesc = {};
	rasterizerdesc.FillMode = D3D11_FILL_SOLID; // ä��� ���
	rasterizerdesc.CullMode = D3D11_CULL_BACK; // �� ���̽� �ø�

	Device->CreateRasterizerState(&rasterizerdesc, &RasterizerState);
}

void CEngine::CreateShader()
{
	ID3DBlob* vertexshaderCSO;
	ID3DBlob* pixelshaderCSO;

	D3DCompileFromFile(L"ShaderW0.hlsl", nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &vertexshaderCSO, nullptr);

	Device->CreateVertexShader(vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), nullptr, &SimpleVertexShader);

	D3DCompileFromFile(L"ShaderW0.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

	Device->CreatePixelShader(pixelshaderCSO->GetBufferPointer(), pixelshaderCSO->GetBufferSize(), nullptr, &SimplePixelShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		/*{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }*/
	};

	Device->CreateInputLayout(layout, ARRAYSIZE(layout),
		vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), &SimpleInputLayout);

	Stride = sizeof(FVertex);

	vertexshaderCSO->Release();
	pixelshaderCSO->Release();
}

void CEngine::Update(float deltaTime)
{
	// ������� ������Ʈ?

}

void CEngine::Render()
{
	// Clear
	DeviceContext->ClearRenderTargetView(FrameBufferRTV, ClearColor);

	// IA
	DeviceContext->IASetInputLayout(SimpleInputLayout);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VS
	DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);

	// RS
	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->RSSetState(RasterizerState);

	// PS
	DeviceContext->PSSetShader(SimplePixelShader, nullptr, 0);

	// OM
	DeviceContext->OMSetRenderTargets(1, &FrameBufferRTV, nullptr);
	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);

	// �׽�Ʈ��
	if (ConstantBuffer && MVPConstantBuffer)
	{
		DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer); 
		DeviceContext->VSSetConstantBuffers(1, 1, &MVPConstantBuffer);
	}

	UpdateConstant({ 0.0f, 0.0f, 0.0f }, 1.0f , modelTest, modelRotTest);

	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &offset);

	const UINT numVertices = sizeof(triangle_vertices) / sizeof(FVertex);
	//

	DeviceContext->Draw(numVertices, 0);
}

void CEngine::Release()
{
	VertexBuffer->Release();

	if (ConstantBuffer)
	{
		ConstantBuffer->Release();
		ConstantBuffer = nullptr;
	}

	// Shader ���� ���ҽ� ����
	if (SimpleInputLayout)
	{
		SimpleInputLayout->Release();
		SimpleInputLayout = nullptr;
	}
	if (SimplePixelShader)
	{
		SimplePixelShader->Release();
		SimplePixelShader = nullptr;
	}
	if (SimpleVertexShader)
	{
		SimpleVertexShader->Release();
		SimpleVertexShader = nullptr;
	}

	RasterizerState->Release();

	// ���� Ÿ���� �ʱ�ȭ
	DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

	// FrameBuffer ���� ���ҽ� ����
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

	// Direct3D ��ġ �� ���� ü���� ����
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
}