#pragma once

#include "Typedef.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "CScene.h"
#include "FVector.h"

using namespace std;

//class TestComponent
//{
//public:
//	float b;
//	int* array;
//};
//class TestActor
//{
//
//public:
//	int a;
//	TestComponent* comp;
//
//};

enum class EComponentType
{
	USceneComponent = 0,
	UCamera = 1,
};
class CSceneManager
{
public:
	const static string UScenePositionNameKey;
	const static string USceneRotationNameKey;
	const static string USceneScaleNameKey;
	const static FString ActorNameKey;
	const static FString USceneComponentNameKey;
	const static FString CurSceneNameKey;
	const static FString SceneNamesKey;
	const static FString SceneFolderPath;
	const static FString SceneManagerInfoPath;
	const static FString DefaultSceneName;

	static CSceneManager* Ins;

private:
	TArray<FString> SceneNames;
	CScene Scene;

public:
	CSceneManager();
	//~CSceneManager();

	//씬을 불러오려면 어떤 씬이 있는지 먼저 알아야 한다.
	//불러올 씬이 없을경우 첫 씬을 생성하도록 한다.
	bool CreateScene(const string& sceneName);
	bool LoadScene(const string& sceneName);
	
	CScene& GetScene()
	{
		return Scene;
	}

private:
	bool CheckExistSceneFileName(const FString& sceneName);
	bool CheckExistSceneFilePath(const FString& sceneFilePath);

	static string GetSceneFilePath(const FString& sceneName);
};