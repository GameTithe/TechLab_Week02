#pragma once
#include "AActor.h"
#include <memory>
class UActorComponent : public UObject
{
	friend class AActor; // AActor�� protected, private ���� �����ϵ���

public:
	UActorComponent(AActor* owner) : OwnerActor(owner), bIsActive(true) {}
	virtual ~UActorComponent() {}

	// ======= �ش� ������Ʈ�� Active ���� ���� ========
	void SetActive(bool active) { bIsActive = active; }
	bool IsActive() { return bIsActive; }
	
	// �ش� ������Ʈ�� ������(AActor) ��ȯ
	virtual AActor* GetActor() const { return OwnerActor; }


protected:
	// ======== ������Ʈ ���� �ֱ� ======== 
	virtual void InitializeComponents() {}
	virtual void BeginPlay() {}
	virtual void Tick(float deltaTime) {}
	virtual void EndPlay() {}
	virtual void DoTick(float deltaTime)
	{
		if (!bIsActive) return;
		Tick(deltaTime);
	}
private:
	AActor* OwnerActor; // ������Ʈ���� AActor�� ���� �����ϵ���
	bool bIsActive;
};