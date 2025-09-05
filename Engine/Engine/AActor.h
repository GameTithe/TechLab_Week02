#pragma once
#include "UObject.h"
#include "USceneComponent.h"
#include "TArray.h"
class AActor : public UObject {
public:
	AActor(USceneComponent* rootComponent);

	// ======= ������ ������Ʈ �߰� �� ���� ========
	void AddComponent(USceneComponent* component);
	void RemoveComponent(USceneComponent* component);

	// ======= AActor�� �����ֱ� �Լ� =========
	void PostInitializeComponents();
	void BeginPlay();
	void Tick(float deltaTime);
	void EndPlay();

	USceneComponent* GetRootComponent() const;
protected:
	USceneComponent* RootComponent;				// ��Ʈ ������Ʈ(USceneComponent)�� ���� AActor�� ��ġ ����
	TArray<UActorComponent*> OwnedComponents;	// ������ ������Ʈ ��� -> ������Ʈ�� Tick ȣ���� ����
}; 