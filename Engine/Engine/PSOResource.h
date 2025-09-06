#pragma once

#include "D3DUtil.h"

namespace PSO
{
ID3D11RasterizerState* RasterizerState;

ID3D11InputLayout* SimpleInputLayout;

ID3D11VertexShader* SimpleVS;

ID3D11PixelShader* SimplePS;
ID3D11PixelShader* PickIDPS;

void InitPSOResource();
}