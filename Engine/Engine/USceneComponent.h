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
  
	void AttachToComponent(USceneComponent* parent); // 부모 컴포넌트에 나의 컴포넌트 부착
	
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
	// Component간의 계층 구조를 위한 멤버들
	USceneComponent* ParentComponent; // nullptr이면 해당 컴포넌트가 루트
	TArray<USceneComponent*> ChildComponents; 

};