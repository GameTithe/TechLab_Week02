#include "CSceneManager.h"
#include "Json.hpp" //무조건 cpp에 있어야함
#include "CEngine.h"
//씬매니저 json 정보구조
//CurSceneName : ""
//SceneNames : ["", "", ""]

//Actor에서 URootComponent부터 DFS로 생성
// 	FVector RelativeLocation;
//	FVector RelativeRotation;
//	FVector RelativeScale3D;
//씬 정보구조
//Actors
//	USceneComponent
//		type : 
//		pos : x, y, z
//		rot : x, y, z
//		scale : x, y, z
//	USceneComponent
//		type : 
//		pos : x, y, z 
//		rot : x, y, z
//		scale : x, y, z
//		USceneComponent
//			type : 
//			pos: x, y, z
//			rot : x, y, z
//			scale : x, y, z

using namespace json;

const string EComponentTypeNameKey = "EComponentType";
const string CSceneManager::UScenePositionNameKey = "RelativeLocation";
const string CSceneManager::USceneRotationNameKey = "RelativeRotation";
const string CSceneManager::USceneScaleNameKey = "RelativeScale3D";
const string CSceneManager::ActorNameKey = "Actors";
const string CSceneManager::USceneComponentNameKey = "USceneComponent";
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
		if (CheckExistSceneFileName(SceneNames[i]))
		{
			LoadScene(SceneNames[i]);
		}
		else
		{
			//씬 생성
			CreateScene(SceneNames[i]);
		}
	}
	
	
}




bool CSceneManager::CreateScene(const string& sceneName)
{
	string sceneFilePath = GetSceneFilePath(sceneName);
	if(CheckExistSceneFilePath(sceneFilePath) == true)
	{
		cout << "씬 파일 존재. FilePath : " << sceneFilePath << endl;
		return false;
	}

	//씬 기본 JSON
	JSON sceneJson;
	JSON cameraJson;
	cameraJson = CSceneManager::USceneComponentNameKey;
	cameraJson[CSceneManager::USceneComponentNameKey][EComponentTypeNameKey] = (int)EComponentType::UCamera;
	cameraJson[CSceneManager::USceneComponentNameKey][CSceneManager::UScenePositionNameKey] = json::Array(0.0f,0.0f,-10.0f);
	cameraJson[CSceneManager::USceneComponentNameKey][CSceneManager::USceneRotationNameKey] = json::Array(0.0f,0.0f,0.0f);
	cameraJson[CSceneManager::USceneComponentNameKey][CSceneManager::USceneScaleNameKey] = json::Array(1.0f,1.0f,1.0f);
	JSON actorJson;
	actorJson = CSceneManager::USceneComponentNameKey;
	actorJson[CSceneManager::USceneComponentNameKey][EComponentTypeNameKey] = (int)EComponentType::USceneComponent;
	actorJson[CSceneManager::USceneComponentNameKey][CSceneManager::UScenePositionNameKey] = json::Array(0.0f,0.0f,0.0f);
	actorJson[CSceneManager::USceneComponentNameKey][CSceneManager::USceneRotationNameKey] = json::Array(0.0f,0.0f,0.0f);
	actorJson[CSceneManager::USceneComponentNameKey][CSceneManager::USceneScaleNameKey] = json::Array(1.0f,1.0f,1.0f);
	sceneJson.append(cameraJson);
	sceneJson.append(actorJson);

	//씬 파일 생성 및 기본 JSON 입력
	ofstream createSceneFileSteam(sceneFilePath);
	createSceneFileSteam << sceneJson;
	createSceneFileSteam.close();

	return true;
}

bool CSceneManager::LoadScene(const string& sceneName)
{
	string sceneFilePath = GetSceneFilePath(sceneName);
	if(CheckExistSceneFilePath(sceneFilePath) == false)
	{
		cout << "씬 파일 없음. FilePath : " << sceneFilePath << endl;
		return false;
	}
	ifstream sceneReadStream(sceneFilePath);
	if (sceneReadStream.is_open())
	{
		stringstream ss;
		ss << sceneReadStream.rdbuf();
		JSON sceneInfoJson = JSON::Load(ss.str());

		Scene.ClearScene();

		for(auto& j : sceneInfoJson.ArrayRange())
		{
			int componentType = j[USceneComponentNameKey][EComponentTypeNameKey].ToInt();
			EComponentType type = (EComponentType)(componentType);

			JSON positionJson = j[USceneComponentNameKey][UScenePositionNameKey];
			JSON rotationJson = j[USceneComponentNameKey][USceneRotationNameKey];
			JSON scaleJson = j[USceneComponentNameKey][USceneScaleNameKey];
			cout<<j[USceneComponentNameKey][EComponentTypeNameKey]<<endl;
			cout<<positionJson<<endl;
			cout<<positionJson[2]<<endl;
			FVector pos;
			FVector rot;
			FVector scale;
			pos.X = positionJson[0].ToFloat();
			pos.Y = positionJson[1].ToFloat();
			pos.Z = positionJson[2].ToFloat();
			rot.X = rotationJson[0].ToFloat();
			rot.Y = rotationJson[1].ToFloat();
			rot.Z = rotationJson[2].ToFloat();
			scale.X = scaleJson[0].ToFloat();
			scale.Y = scaleJson[1].ToFloat();
			scale.Z = scaleJson[2].ToFloat();
			switch(type)
			{
			case EComponentType::USceneComponent:
			{
				AActor* actor = Scene.CreateActor();
				actor->GetRootComponent()->SetRelativeLocation(pos);
				actor->GetRootComponent()->SetRelativeRotation(rot);
				actor->GetRootComponent()->SetRelativeScale3D(scale);
			}
					break;
				case EComponentType::UCamera:
				CEngine::gpCEngine->CamPos = pos;
				CEngine::gpCEngine->CamRot = rot;
					break;
			}
		}

		//코드 추가 필요
		return true;
	}
	else
	{
		return false;
	}
}

bool CSceneManager::CheckExistSceneFileName(const string& sceneName)
{
	ifstream sceneNamesReadStream(GetSceneFilePath(sceneName));
	return sceneNamesReadStream.good();
}
bool CSceneManager::CheckExistSceneFilePath(const string& sceneFilePath)
{
	ifstream sceneNamesReadStream(sceneFilePath);
	return sceneNamesReadStream.good();
}



string CSceneManager::GetSceneFilePath(const string& sceneName)
{
	string path = SceneFolderPath;
	path.append(sceneName + ".txt");
	return path;
}
