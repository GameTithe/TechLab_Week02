#include "CSceneManager.h"
#include "Json.hpp" //무조건 cpp에 있어야함

//씬매니저 json 정보구조
//CurSceneName : ""
//SceneNames : ["", "", ""]


using namespace json;

const string CSceneManager::CurSceneNameKey = "CurSceneName";
const string CSceneManager::SceneNamesKey = "SceneNames";
const string CSceneManager::SceneFolderPath = ".\\";
const string CSceneManager::SceneManagerInfoPath = ".\\SceneManagerInfo.txt";
const string CSceneManager::DefaultSceneName = "DefaultScene";

CSceneManager::CSceneManager()
{
	//씬매니저 정보 적힌 파일 찾기
	ifstream sceneMangerInfoReadStream(SceneManagerInfoPath);
	if (sceneMangerInfoReadStream.good() == false)
	{
		//씬매니저 정보 적힌 파일 생성
		ofstream createFileStream(SceneManagerInfoPath);
		JSON sceneManagerInfoJson;

		//씬매니저 정보 초기 데이터 세팅
		sceneManagerInfoJson[CurSceneNameKey] = DefaultSceneName;
		sceneManagerInfoJson[SceneNamesKey] = Array(DefaultSceneName);
		createFileStream << sceneManagerInfoJson;
		createFileStream.close();
	}

	sceneMangerInfoReadStream = ifstream(SceneManagerInfoPath);
	if (sceneMangerInfoReadStream.is_open())
	{
		stringstream ss;
		ss << sceneMangerInfoReadStream.rdbuf();
		JSON sceneManagerInfoJson = JSON::Load(ss.str());
		string temp = sceneManagerInfoJson[CurSceneNameKey].ToString();
		for (auto& j : sceneManagerInfoJson[SceneNamesKey].ArrayRange())
		{
			SceneNames.push_back(j.ToString());
		}
		sceneMangerInfoReadStream.close();

		//씬 이름이 없을경우
		if (SceneNames.size() == 0)
		{
			//default 씬 이름 추가
			ofstream sceneMangerInfoWriteStream(SceneManagerInfoPath);
			if (sceneMangerInfoWriteStream.is_open())
			{
				JSON sceneManagerInfoJson;
				sceneManagerInfoJson[CurSceneNameKey] = DefaultSceneName;
				sceneManagerInfoJson[SceneNamesKey] = Array(DefaultSceneName);
				sceneMangerInfoWriteStream << sceneManagerInfoJson;
				sceneMangerInfoWriteStream.close();
			}

			//SceneNames파일에 DefaultScene추가
			SceneNames.push_back(DefaultSceneName);
		}
	}
	else
	{
		cout << "SceneNamesPath text file open error " << endl;
		return;
	}
	

	int sceneNameCount = SceneNames.size();
	if (sceneNameCount <= 0)
	{
		cout << "SceneNameCount is zero" << endl;
		return;
	}

	for (int i = 0; i < sceneNameCount; i++)
	{
		if (CheckExistSceneFile(SceneNames[i]))
		{
			//LoadScene(SceneNames[i], )
		}
		else
		{
			//씬 생성
			//CreateScene(SceneNames[i]);
		}
	}
	
	
}
bool CSceneManager::CreateScene(const string& sceneName)
{
	ifstream sceneReadStream(GetSceneFilePath(sceneName));
	if (sceneReadStream.is_open())
	{
		stringstream ss;
		ss << sceneReadStream.rdbuf();
		JSON sceneNamesJson = JSON::Load(ss.str());

		//코드 추가 필요
		return true;
	}
	else
	{
		return false;
	}
}

bool CSceneManager::LoadScene(const string& sceneName, CScene& outScene)
{
	ifstream sceneNamesReadStream(GetSceneFilePath(sceneName));
	if (sceneNamesReadStream.is_open())
	{
		stringstream ss;
		ss << sceneNamesReadStream.rdbuf();
		JSON sceneNamesJson = JSON::Load(ss.str());

		//코드 추가 필요
		return true;
	}
	else
	{
		return false;
	}
}

bool CSceneManager::CheckExistSceneFile(const string& sceneName)
{
	ifstream sceneNamesReadStream(GetSceneFilePath(sceneName));
	return sceneNamesReadStream.good();
}

string CSceneManager::GetSceneFilePath(const string& sceneName)
{
	string path = SceneFolderPath;
	path.append(sceneName + ".txt");
	return path;
}
