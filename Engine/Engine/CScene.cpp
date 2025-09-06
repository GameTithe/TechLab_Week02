#include "CScene.h"
#include "PSOResource.h"
#include "PipelineStateObject.h"
#include "CEngine.h"
void CScene::ClearScene()
{

}
FVector tempPos;
AActor* CScene::CreateActor()
{
	AActor* actor = new AActor();
	actor->GetRootComponent()->SetRelativeLocation(tempPos);
	tempPos.X += 2;
	SceneActors.push_back(actor);
	return actor;
}
void CScene::DestroyActor()
{
	if(SceneActors.size() == 0)
	{
		return;
	}
	AActor* lastActor = SceneActors.back();
	delete lastActor;
	SceneActors.pop_back();
}

void CScene::RenderPickingScene()
{
	
	///D3DUtil::CBufferUpdate(DeviceContext, )

	FObjectPicking pickingData;
	pickingData.Pick = 0;
	PSO::PickingPSO->SetRenderState();
	int actorCount = SceneActors.size();
	for(int i=0;i<actorCount;i++)
	{
		pickingData.ObjectID = i + 1;
		D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),CEngine::gpCEngine->GetPickingCBuffer(),pickingData);
		//SceneActors[i]->Render();
	}
}
void CScene::RenderScene()
{
	FObjectPicking pickingData;
	pickingData.Pick = CEngine::gpCEngine->GetPickID();
	PSO::SimplePSO->SetRenderState();
	int actorCount = SceneActors.size();
	for(int i=0;i<actorCount;i++)
	{
		pickingData.ObjectID = i + 1;
		D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),CEngine::gpCEngine->GetPickingCBuffer(),pickingData);
		//SceneActors[i]->Render();
	}
}