#include "CScene.h"
#include "PSOResource.h"
#include "PipelineStateObject.h"
#include "CEngine.h"
#include "UCubeComponent.h"
void CScene::ClearScene()
{

}
FVector tempPos;
AActor* CScene::CreateActor()
{
	AActor* actor = new AActor();
	actor->SetRootComponent(new UCubeComponent());
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
	TArray<UPrimitiveComponent*> renderComponents;

	for(int i=0;i<actorCount;i++)
	{
		AActor* curActor = SceneActors[i];
		
		//활성화 된 PrimitiveComponent만 가져오기
		curActor->GetPrimitiveComponents(renderComponents);
	}

	for(UPrimitiveComponent* primitive : renderComponents)
	{
		primitive->UpdateConstantBuffer();
		primitive->Render();
	}

	/*renderComponents.push_back(curActor->GetRootComponent());

	pickingData.ObjectID = i + 1;
	D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),CEngine::gpCEngine->GetPickingCBuffer(),pickingData);*/
	//SceneActors[i]->Render();
}