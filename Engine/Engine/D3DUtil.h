#pragma once

//.lib파일 링킹 지시문
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>

using namespace std;
class D3DUtil
{
	//vertexbuffer 생성 => FVertex 필요
	//indexbuffer 생성
	//VS, InputLayout 생성
	//PS 생성
	//CBuffer생성
	//CBuffer 업데이트 <T>

public:

	template <typename T>
	static void CBufferUpdate(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, T& cBufferData)
	{
		D3D11_MAPPED_SUBRESOURCE cBufferMSR;

		//gpu메모리를 cpu가 접근할 수 있도록 잠금
		//D3D11_MAP_WRITE_DISCARD : gpu안의 데이터를 버리고 cpu에서 넣는 데이터로 덮어씌움 
		//gpu내용을 버림으로써 gpu안의 메모리를 읽는 과정 생략
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