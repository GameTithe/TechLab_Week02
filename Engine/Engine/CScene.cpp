#include "CScene.h"
#include "PSOResource.h"
#include "PipelineStateObject.h"
#include "CEngine.h"
#include "UCubeComponent.h"
void CScene::ClearScene()
{

}
AActor* CScene::CreateActor()
{
	AActor* actor = new AActor();
	actor->SetRootComponent(new UCubeComponent());
	
	actor->GetRootComponent()->SetRelativeLocation(FVector(0,0,0));
	SceneActors.push_back(actor);
	return actor;
}
void CScene::DestroySceneComponent(UPrimitiveComponent* primitive)
{
	//루트일 경우 Actor삭제
	if(primitive->GetOwner()->GetRootComponent() == primitive)
	{
		AActor* lastActor = SceneActors.back();
		delete lastActor;
		SceneActors.pop_back();
	}


	//현재 제거되는 UPrimitiveComponent의 자식 까지 모두 삭제

}
UPrimitiveComponent* CScene::GetPrimitiveComponent(int uuid)
{
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
		if(primitive->GetUUID() == uuid)
		{
			return primitive;
		}
	}
	return nullptr;
}

void CScene::RenderPickingScene()
{
	
	FObjectPicking pickingData;
	pickingData.Pick = 0;
	PSO::PickingPSO->SetRenderState();
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
		uint32 uuid = primitive->GetUUID();
		pickingData.ObjectID = uuid;
		D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),CEngine::gpCEngine->GetPickingCBuffer(),pickingData);
			primitive->UpdateConstantBuffer();
		primitive->Render();
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
		uint32 uuid = primitive->GetUUID();
		pickingData.ObjectID = uuid;
		D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),CEngine::gpCEngine->GetPickingCBuffer(),pickingData);
		primitive->UpdateConstantBuffer();
		primitive->Render();
	}

	/*renderComponents.push_back(curActor->GetRootComponent());

	pickingData.ObjectID = i + 1;
	D3DUtil::CBufferUpdate(CEngine::gpCEngine->GetDeviceContext(),CEngine::gpCEngine->GetPickingCBuffer(),pickingData);*/
	//SceneActors[i]->Render();
}