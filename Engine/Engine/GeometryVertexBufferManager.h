#pragma once
#include "UGeometry.h"
#include "D3DUtil.h"
class GeometryVertexBufferManager
{
public:
	static GeometryVertexBufferManager& GetInstance()
	{
		static GeometryVertexBufferManager instance;
		return instance;
	}
	void Init();
	ID3D11Buffer* GetSphereVertexBuffer() const;
	ID3D11Buffer* GetCubeVertexBuffer() const;
	ID3D11Buffer* GetPlaneVertexBuffer() const;

private:
	ID3D11Buffer* SphereVertexBuffer; 
	ID3D11Buffer* CubeVertexBuffer;
	ID3D11Buffer* PlaneVertexBuffer;
	GeometryVertexBufferManager() = default;
	~GeometryVertexBufferManager();

	GeometryVertexBufferManager(const GeometryVertexBufferManager&) = delete;
	GeometryVertexBufferManager& operator=(const GeometryVertexBufferManager&) = delete;
};