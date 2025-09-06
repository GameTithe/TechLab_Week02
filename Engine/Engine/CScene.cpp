#include "CScene.h"
#include "PSOResource.h"
#include "PipelineStateObject.h"
void CScene::ClearScene()
{

}
AActor* CScene::CreateActor()
{
	AActor* actor = new AActor();
	SceneActors.push_back(actor);
	return actor;
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