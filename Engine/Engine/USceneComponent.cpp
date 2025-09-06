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

FMatrix USceneComponent::GetModelMatrix()
{

	return ModelMatrix;
}

void USceneComponent::UpdateModelMatrix()
{
	// 상대 Transform으로 상대 행렬 구하기
	// Calculate relative matrix(transform matrix) using relative transform
	FMatrix relativeMatrix = FMatrix::MakeScaleMatrix(RelativeScale3D.X, RelativeScale3D.Y, RelativeScale3D.Z)
		* FMatrix::MakeRotationXMatrix(RelativeRotation.X)
		* FMatrix::MakeRotationYMatrix(RelativeRotation.Y)
		* FMatrix::MakeRotationZMatrix(RelativeRotation.Z)
		* FMatrix::MakeTranslationMatrix({ RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z, 1 });
	if (!ParentComponent)
	{
		// 부모가 없으면
		// 나의 Model Matrix = 계산한 상대 행렬
		// my model matrix is just relative matrix calculated 
		ModelMatrix = relativeMatrix;
	}
	else
	{
		// 부모 있으면
		// 나의 Model Matrix = 계산한 상대 행렬 * 부모의 Model Matrix
		// my model matrix is relative matrix * parent's model matrix
		ModelMatrix = relativeMatrix * ParentComponent->GetModelMatrix();
		
	}
	// 자식 컴포넌트에 부모의 Model Matrix 변경됨을 전파
	for (USceneComponent* child : ChildComponents)
	{
		child->UpdateModelMatrix();
	}
	
}
