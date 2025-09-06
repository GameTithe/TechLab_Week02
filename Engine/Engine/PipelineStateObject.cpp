#include "PipelineStateObject.h"
#include "CEngine.h"

void CPipelineStateObject::SetRenderState()
{
	CEngine::gpCEngine->GetDeviceContext()->OMSetBlendState(BlendState, nullptr, 0xffffffff);
	CEngine::gpCEngine->GetDeviceContext()->OMSetDepthStencilState(DepthStencilState, 0);

	CEngine::gpCEngine->GetDeviceContext()->RSSetState(RasterizerState);
	CEngine::gpCEngine->GetDeviceContext()->IASetInputLayout(Inputlayout);

	CEngine::gpCEngine->GetDeviceContext()->VSSetShader(VS, 0, 0);
	CEngine::gpCEngine->GetDeviceContext()->PSSetShader(PS, 0, 0);
}