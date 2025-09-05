#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "CScene.h"

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


class CSceneManager
{
public:
	const static string CurSceneNameKey;
	const static string SceneNamesKey;
	const static string SceneFolderPath;
	const static string SceneManagerInfoPath;
	const static string DefaultSceneName;

private:
	vector<string> SceneNames;

public:
	CSceneManager();
	//~CSceneManager();


	//씬을 불러오려면 어떤 씬이 있는지 먼저 알아야 한다.
	//불러올 씬이 없을경우 첫 씬을 생성하도록 한다.
	bool CreateScene(const string& sceneName);
	bool LoadScene(const string& sceneName, CScene& outScene);
	//bool SaveScene(const string& sceneName);

	//void CreateActor();
	//void RemoveActor();

private:
	bool CheckExistSceneFile(const string& sceneName);

	static string GetSceneFilePath(const string& sceneName);
};