#pragma once
#include "UActorComponent.h"
#include "FVector.h"

class USceneComponent : public UActorComponent
{
public:
	USceneComponent();
	virtual ~USceneComponent();

	// ======= ���� ���� =========
	FVector GetWorldLocation();
	FVector SetWorldLocation(FVector Location);

	// ======== �θ� ������Ʈ�� �ش� ������Ʈ�� ���� ========
	void AttachToComponent(USceneComponent* parent);
	
public:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D;

protected:
	USceneComponent* ParentComponent;			// ���� ���� ������ ���� (�𸮾󿡼��� Component���� ��������)
	TArray<USceneComponent*> ChildComponents;   // ���� ���� ������ ����
};