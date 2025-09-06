#pragma once
#include "UGeometry.h"
#include "D3DUtil.h"
class GeometryVertexBufferManager
{
public:

	static GeometryVertexBufferManager& GetInstance() {
		static GeometryVertexBufferManager instance;
		if(!instance.bIsInitialized) {
			instance.Init(); // 최초 접근 시 자동 초기화
			
		}
		return instance;
	}
	void Init();
	ID3D11Buffer* GetSphereVertexBuffer() const;
	ID3D11Buffer* GetCubeVertexBuffer() const;
	ID3D11Buffer* GetPlaneVertexBuffer() const;

	int GetNumSphereVertices();
	int GetNumCubeVertices();
	int GetNumPlaneVertices();
private:
	bool bIsInitialized = false;
	ID3D11Buffer* SphereVertexBuffer; 
	ID3D11Buffer* CubeVertexBuffer;
	ID3D11Buffer* PlaneVertexBuffer;
	
	int NumSphereVertices;
	int NumCubeVertices;
	int NumPlaneVertices;

	GeometryVertexBufferManager() = default;
	~GeometryVertexBufferManager();

	GeometryVertexBufferManager(const GeometryVertexBufferManager&) = delete;
	GeometryVertexBufferManager& operator=(const GeometryVertexBufferManager&) = delete;
};