#include <algorithm>
#include "AActor.h"

AActor::AActor(USceneComponent* rootComponent) : RootComponent(rootComponent)
{
	OwnedComponents.push_back(static_cast<UActorComponent*>(rootComponent));
}

void AActor::AddComponent(USceneComponent* component)
{
	OwnedComponents.push_back(static_cast<UActorComponent*>(component));
}

void AActor::RemoveComponent(USceneComponent* component)
{
	OwnedComponents.erase(std::remove(OwnedComponents.begin(), OwnedComponents.end(), component), OwnedComponents.end());
}
void AActor::PostInitializeComponents()
{

}
void AActor::BeginPlay()
{

}

void AActor::Tick(float deltaTime)
{
	for (const auto& component : OwnedComponents)
	{
		if (component && !component->IsActive())
		{
			component->DoTick(deltaTime);
		}
	}
}

void AActor::EndPlay()
{

}

USceneComponent* AActor::GetRootComponent() const
{
	return RootComponent; 
}
