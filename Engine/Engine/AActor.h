#pragma once
#include "UObject.h"
#include "USceneComponent.h"
#include "TArray.h"
class AActor : public UObject {
public:
	AActor(USceneComponent* rootComponent);

	// ======= 소유할 컴포넌트 추가 및 삭제 ========
	void AddComponent(USceneComponent* component);
	void RemoveComponent(USceneComponent* component);

	// ======= AActor의 생명주기 함수 =========
	void PostInitializeComponents();
	void BeginPlay();
	void Tick(float deltaTime);
	void EndPlay();

	USceneComponent* GetRootComponent() const;
protected:
	USceneComponent* RootComponent;				// 루트 컴포넌트(USceneComponent)를 통해 AActor의 위치 결정
	TArray<UActorComponent*> OwnedComponents;	// 소유한 컴포넌트 목록 -> 컴포넌트의 Tick 호출을 위함
}; 