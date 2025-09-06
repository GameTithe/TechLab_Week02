#include "GeometryVertexBufferManager.h"

void GeometryVertexBufferManager::Init()
{
    bIsInitialized = true;
    // TODO: D3DUtil 이용해 기본 Primitive 버퍼 생성
    D3DUtil::CreateVertexBuffer(sphere_vertices,&SphereVertexBuffer, sizeof(sphere_vertices));
    D3DUtil::CreateVertexBuffer(cube_vertices, &CubeVertexBuffer, sizeof(cube_vertices));
    D3DUtil::CreateVertexBuffer(plane_vertices, &PlaneVertexBuffer, sizeof(plane_vertices));
    
}

ID3D11Buffer* GeometryVertexBufferManager::GetSphereVertexBuffer() const
{
    return SphereVertexBuffer;
}

ID3D11Buffer* GeometryVertexBufferManager::GetCubeVertexBuffer() const
{
    return CubeVertexBuffer;
}

ID3D11Buffer* GeometryVertexBufferManager::GetPlaneVertexBuffer() const
{
    return PlaneVertexBuffer;
}

GeometryVertexBufferManager::~GeometryVertexBufferManager()
{
    SphereVertexBuffer->Release();
    CubeVertexBuffer->Release();
    PlaneVertexBuffer->Release();
}
