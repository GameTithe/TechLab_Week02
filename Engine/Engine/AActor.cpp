#include <algorithm>
#include "AActor.h"

AActor::AActor()
{
	USceneComponent* rootComponent = new USceneComponent(this);
	SetRootComponent(rootComponent); // 생성자에서 기본으로 루트 컴포넌트 설정
}

void AActor::SetRootComponent(USceneComponent* rootComponent)
{
	RootComponent = rootComponent;
	OwnedComponents.push_back(RootComponent);
}
 
void AActor::AddComponent(UActorComponent* component)
{
	if (component == nullptr) return;
	// 소유 컴포넌트 목록에 추가
	OwnedComponents.push_back(component);
	
	// USceneComponent* 라면 컴포넌트 계층구조 자동 설정 (루트 컴포넌트에 붙여준다)
	USceneComponent* childComponent = dynamic_cast<USceneComponent*>(component);
	if (childComponent && RootComponent)
	{
		childComponent->AttachToComponent(RootComponent);
	}
}

void AActor::AddComponent(UActorComponent* component, USceneComponent* parent)
{
	if (component == nullptr || parent == nullptr) return;
	
	OwnedComponents.push_back(component);

	// USceneComponent* 라면 컴포넌트 계층구조 자동 설정 (인자로 받은 parent에 붙여준다)
	USceneComponent* childComponent = dynamic_cast<USceneComponent*>(component);
	if (childComponent && parent)
	{
		childComponent->AttachToComponent(parent);
	}
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

