#pragma once

//.lib���� ��ŷ ���ù�
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>

using namespace std;
class D3DUtil
{
	//vertexbuffer ���� => FVertex �ʿ�
	//indexbuffer ����
	//VS, InputLayout ����
	//PS ����
	//CBuffer����
	//CBuffer ������Ʈ <T>

public:

	template <typename T>
	static void CBufferUpdate(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, T& cBufferData)
	{
		D3D11_MAPPED_SUBRESOURCE cBufferMSR;

		//gpu�޸𸮸� cpu�� ������ �� �ֵ��� ���
		//D3D11_MAP_WRITE_DISCARD : gpu���� �����͸� ������ cpu���� �ִ� �����ͷ� ����� 
		//gpu������ �������ν� gpu���� �޸𸮸� �д� ���� ����
		context->Map(cBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &cBufferMSR);
		memcpy(cBufferMSR.pData, &cBufferData, sizeof(T));
		context->Unmap(cBuffer, 0);
	}
	template <typename T>
	static void CreateCBufferUpdate(ID3D11DeviceContext* context, ID3D11Buffer** cBuffer, T& cBufferData)
	{
		CreateCBuffer(cBuffer);
		CBufferUpdate(context, *cBuffer, cBufferData);
	}

	static void CreateCBuffer(ID3D11Buffer** cBuffer);
	static void CreateVertexBuffer(ID3D11Buffer** vertexBuffer);
	static void CreateIndexBuffer(ID3D11Buffer** indexBuffer);
	static void CreateVSAndInputLayout(const wstring& filePath, ID3D11VertexShader** vs, ID3D11InputLayout** inputLayout, D3D11_INPUT_ELEMENT_DESC& inputLayoutDesc);
	static void CreatePS(const wstring& filePath, ID3D11PixelShader** ps);
};