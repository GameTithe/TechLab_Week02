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
	// ë‚˜ì˜ ë¶€ëª¨ ì»´í¬ë„ŒíŠ¸ê°€ ì¡´ìž¬í•˜ë©´
	if (ParentComponent)
	{
		// ë¶€ëª¨ ì»´í¬ë„ŒíŠ¸ì˜ ìžì‹ ëª©ë¡ì—ì„œ ë‚˜ë¥¼ ì œê±°
		ParentComponent->ChildComponents.erase(
			std::remove(ParentComponent->ChildComponents.begin(), ParentComponent->ChildComponents.end(), this), 
			ParentComponent->ChildComponents.end());
	} 

	// ë‚˜ì˜ ìƒˆ ë¶€ëª¨ ì„¤ì •
	ParentComponent = parent;

	// ë¶€ëª¨ì˜ ìžì‹ ëª©ë¡ì— ë‚˜ ì¶”ê°€
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
	// »ó´ë TransformÀ¸·Î »ó´ë Çà·Ä ±¸ÇÏ±â
	// Calculate relative matrix(transform matrix) using relative transform
	FMatrix relativeMatrix = FMatrix::MakeScaleMatrix(RelativeScale3D.X, RelativeScale3D.Y, RelativeScale3D.Z)
		* FMatrix::MakeRotationXMatrix(RelativeRotation.X)
		* FMatrix::MakeRotationYMatrix(RelativeRotation.Y)
		* FMatrix::MakeRotationZMatrix(RelativeRotation.Z)
		* FMatrix::MakeTranslationMatrix({ RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z, 1 });
	if (!ParentComponent)
	{
		// ºÎ¸ð°¡ ¾øÀ¸¸é
		// ³ªÀÇ Model Matrix = °è»êÇÑ »ó´ë Çà·Ä
		// my model matrix is just relative matrix calculated 
		ModelMatrix = relativeMatrix;
	}
	else
	{
		// ºÎ¸ð ÀÖÀ¸¸é
		// ³ªÀÇ Model Matrix = °è»êÇÑ »ó´ë Çà·Ä * ºÎ¸ðÀÇ Model Matrix
		// my model matrix is relative matrix * parent's model matrix
		ModelMatrix = relativeMatrix * ParentComponent->GetModelMatrix();
		
	}
	// ÀÚ½Ä ÄÄÆ÷³ÍÆ®¿¡ ºÎ¸ðÀÇ Model Matrix º¯°æµÊÀ» ÀüÆÄ
	for (USceneComponent* child : ChildComponents)
	{
		child->UpdateModelMatrix();
	}
	
}
