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

FMatrix USceneComponent::GetModelMatrix()
{

	return ModelMatrix;
}

void USceneComponent::UpdateModelMatrix()
{
	// ��� Transform���� ��� ��� ���ϱ�
	// Calculate relative matrix(transform matrix) using relative transform
	FMatrix relativeMatrix = FMatrix::MakeScaleMatrix(RelativeScale3D.X, RelativeScale3D.Y, RelativeScale3D.Z)
		* FMatrix::MakeRotationXMatrix(RelativeRotation.X)
		* FMatrix::MakeRotationYMatrix(RelativeRotation.Y)
		* FMatrix::MakeRotationZMatrix(RelativeRotation.Z)
		* FMatrix::MakeTranslationMatrix({ RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z, 1 });
	if (!ParentComponent)
	{
		// �θ� ������
		// ���� Model Matrix = ����� ��� ���
		// my model matrix is just relative matrix calculated 
		ModelMatrix = relativeMatrix;
	}
	else
	{
		// �θ� ������
		// ���� Model Matrix = ����� ��� ��� * �θ��� Model Matrix
		// my model matrix is relative matrix * parent's model matrix
		ModelMatrix = relativeMatrix * ParentComponent->GetModelMatrix();
		
	}
	// �ڽ� ������Ʈ�� �θ��� Model Matrix ������� ����
	for (USceneComponent* child : ChildComponents)
	{
		child->UpdateModelMatrix();
	}
	
}
