#pragma once
#include "UActorComponent.h"
#include "FVector.h"
#include "FMatrix.h"
#include "Typedef.h"
class USceneComponent : public UActorComponent
{
public:
	USceneComponent();
	USceneComponent(AActor* owner);
	virtual ~USceneComponent();
  
	void AttachToComponent(USceneComponent* parent); // �θ� ������Ʈ�� ���� ������Ʈ ����
	
	void SetRelativeLocation(FVector relativeLocation);
	void SetRelativeRotation(FVector relativeRotaition);
	void SetRelativeScale3D(FVector relativeScale3D);

	FVector GetRelativeLocation();
	FVector GetRelativeRotation();
	FVector GetRelativeScale3D();

	FVector GetWorldLocation();
	FVector GetWorldRotation();
	FVector GetWorldScale3D();

	void UpdateWorldTransform();
private:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D;
	FMatrix ModelMatrix;
protected:
	// Component���� ���� ������ ���� �����
	USceneComponent* ParentComponent; // nullptr�̸� �ش� ������Ʈ�� ��Ʈ
	TArray<USceneComponent*> ChildComponents; 

};