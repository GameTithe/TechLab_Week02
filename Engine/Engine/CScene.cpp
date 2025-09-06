#include "CScene.h"

void CScene::ClearScene()
{

}
AActor* CScene::CreateActor()
{
	AActor* actor = new AActor();
	GUObjectArray.push_back(actor);
	return actor;
}