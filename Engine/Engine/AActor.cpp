#include <algorithm>
#include "AActor.h"

AActor::AActor()
{
	USceneComponent* rootComponent = new USceneComponent(this);
	SetRootComponent(rootComponent); // �����ڿ��� �⺻���� ��Ʈ ������Ʈ ����
}

void AActor::SetRootComponent(USceneComponent* rootComponent)
{
	RootComponent = rootComponent;
	OwnedComponents.push_back(RootComponent);
}

void AActor::AddComponent(UActorComponent* component)
{
	if (component == nullptr) return;
	// ���� ������Ʈ ��Ͽ� �߰�
	OwnedComponents.push_back(component);
	
	// USceneComponent* ��� ������Ʈ �������� �ڵ� ���� (��Ʈ ������Ʈ�� �ٿ��ش�)
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

	// USceneComponent* ��� ������Ʈ �������� �ڵ� ���� (���ڷ� ���� parent�� �ٿ��ش�)
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

