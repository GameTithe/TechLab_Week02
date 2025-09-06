#include "CScene.h"
#include "PSOResource.h"
#include "PipelineStateObject.h"
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
	PSO::PickingPSO->SetRenderState();

	int actorCount = SceneActors.size();
	for(int i=0;i<actorCount;i++)
	{
		SceneActors[i]->Render();
	}
}
void CScene::RenderScene()
{
	PSO::SimplePSO->SetRenderState();

	int actorCount = SceneActors.size();
	for(int i=0;i<actorCount;i++)
	{
		SceneActors[i]->Render();
	}
}