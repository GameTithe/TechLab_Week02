#include "USceneComponent.h"

USceneComponent::USceneComponent()
{
}

USceneComponent::USceneComponent(AActor* owner): UActorComponent(owner)
{
}

USceneComponent::~USceneComponent()
{
}

void USceneComponent::AttachToComponent(USceneComponent* parent)
{
	// 나의 부모 컴포넌트가 존재하면
	if (ParentComponent)
	{
		// 부모 컴포넌트의 자식 목록에서 나를 제거
		ParentComponent->ChildComponents.erase(
			std::remove(ParentComponent->ChildComponents.begin(), ParentComponent->ChildComponents.end(), this), 
			ParentComponent->ChildComponents.end());
	}

	// 나의 새 부모 설정
	ParentComponent = parent;

	// 부모의 자식 목록에 나 추가
	if (parent)
	{
		ParentComponent->ChildComponents.push_back(this);
	}

}

void USceneComponent::SetRelativeLocation(FVector relativeLocation)
{
	RelativeLocation = relativeLocation;
}

void USceneComponent::SetRelativeRotation(FVector relativeRotaition)
{
	RelativeRotation = relativeRotaition;
}

void USceneComponent::SetRelativeScale3D(FVector relativeScale3D)
{
	RelativeScale3D = relativeScale3D;
}

FVector USceneComponent::GetRelativeLocation()
{
	return RelativeLocation;
}

FVector USceneComponent::GetRelativeRotation()
{
	return RelativeRotation;
}

FVector USceneComponent::GetRelativeScale3D()
{
	return RelativeScale3D;
}


FVector USceneComponent::GetWorldLocation()
{
	return FVector();
}

FVector USceneComponent::GetWorldRotation()
{
	return FVector();
}

FVector USceneComponent::GetWorldScale3D()
{
	return FVector();
}

void USceneComponent::UpdateWorldTransform()
{
	if (ParentComponent)
	{
		//ModelMatix = FMatrix::Make
	}
	
}
