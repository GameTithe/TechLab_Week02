#pragma once

#include "D3DUtil.h"
#include "PipelineStateObject.h"

namespace PSO
{
extern ID3D11RasterizerState* RasterizerState;
extern ID3D11InputLayout* SimpleInputLayout;
extern ID3D11VertexShader* SimpleVS;
extern ID3D11PixelShader* SimplePS;
extern ID3D11PixelShader* MousePickingPS;
extern CPipelineStateObject* SimplePSO;
extern CPipelineStateObject* MousePickingPSO;

void InitPSOResource();
void ReleasePSOResource();
}