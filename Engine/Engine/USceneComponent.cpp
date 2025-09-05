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
	// ���� �θ� ������Ʈ�� �����ϸ�
	if (ParentComponent)
	{
		// �θ� ������Ʈ�� �ڽ� ��Ͽ��� ���� ����
		ParentComponent->ChildComponents.erase(
			std::remove(ParentComponent->ChildComponents.begin(), ParentComponent->ChildComponents.end(), this), 
			ParentComponent->ChildComponents.end());
	}

	// ���� �� �θ� ����
	ParentComponent = parent;

	// �θ��� �ڽ� ��Ͽ� �� �߰�
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
