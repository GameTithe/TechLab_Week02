#pragma once

// 아래 것들은 나중에 삭제 예정
#include "UObject.h"
#include "AActor.h"
#include "Typedef.h"


class CScene
{
public:
	TArray<AActor*> SceneActors;
public:
	
	void ClearScene();
	AActor* CreateActor();

	void RenderPickingScene();
	void RenderScene();
	
};
 