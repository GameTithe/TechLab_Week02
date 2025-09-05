#pragma once
#include "UActorComponent.h"
#include "FVector.h"

class USceneComponent : public UActorComponent
{
public:
	USceneComponent();
	virtual ~USceneComponent();

	// ======= 연산 관련 =========
	FVector GetWorldLocation();
	FVector SetWorldLocation(FVector Location);

	// ======== 부모 컴포넌트에 해당 컴포넌트를 부착 ========
	void AttachToComponent(USceneComponent* parent);
	
public:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D;

protected:
	USceneComponent* ParentComponent;			// 계층 구조 관리를 위함 (언리얼에서는 Component간의 계층구조)
	TArray<USceneComponent*> ChildComponents;   // 계층 구조 관리를 위함
};