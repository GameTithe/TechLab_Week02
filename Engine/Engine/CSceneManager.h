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


	//���� �ҷ������� � ���� �ִ��� ���� �˾ƾ� �Ѵ�.
	//�ҷ��� ���� ������� ù ���� �����ϵ��� �Ѵ�.
	bool CreateScene(const string& sceneName);
	bool LoadScene(const string& sceneName, CScene& outScene);
	//bool SaveScene(const string& sceneName);

	//void CreateActor();
	//void RemoveActor();

private:
	bool CheckExistSceneFile(const string& sceneName);

	static string GetSceneFilePath(const string& sceneName);
};