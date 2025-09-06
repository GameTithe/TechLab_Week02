#pragma once
#include "UObject.h"
#include "UActorComponent.h"
#include "USceneComponent.h"
class AActor : public UObject {
public:
	AActor();

	// ======= 소유할 컴포넌트 추가 및 삭제 ========
	// 내부적으로 컴포넌트 간 계층 구조는 알아서 등록
	void AddComponent(UActorComponent* component);
	void AddComponent(UActorComponent* component, USceneComponent * parent);
	void RemoveComponent(USceneComponent* component);

	/*void RegisterComponent(UActorComponent* newComponent);

	template<typename T>
	T* CreateAndRegisterComponent()
	{
		T* newComponent = new T();
		RegisterComponent(newComponent);
		return newComponent;
	}*/

	// ======= AActor의 생명주기 함수 =========
	void PostInitializeComponents();
	void BeginPlay();
	void Tick(float deltaTime);
	void EndPlay();

	// ======= 루트 컴포넌트 접근 =======
	USceneComponent* GetRootComponent() const;

protected:
	void SetRootComponent(USceneComponent* rootComponent);
protected:
	USceneComponent* RootComponent;				// 루트 컴포넌트(USceneComponent)를 통해 AActor의 월드 위치, 회전, 크기 담당
	TArray<UActorComponent*> OwnedComponents;	// '소유'한 컴포넌트 목록 -> 컴포넌트의 생명주기 함수 호출을 위함
}; 