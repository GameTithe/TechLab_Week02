#pragma once
#include "AActor.h"
#include <memory>
class UActorComponent : public UObject
{
	friend class AActor; // AActor는 protected, private 접근 가능하도록

public:
	UActorComponent(AActor* owner) : OwnerActor(owner), bIsActive(true) {}
	virtual ~UActorComponent() {}

	// ======= 해당 컴포넌트의 Active 상태 관리 ========
	void SetActive(bool active) { bIsActive = active; }
	bool IsActive() { return bIsActive; }
	
	// 해당 컴포넌트의 소유자(AActor) 반환
	virtual AActor* GetActor() const { return OwnerActor; }


protected:
	// ======== 컴포넌트 생명 주기 ======== 
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
	AActor* OwnerActor; // 컴포넌트에서 AActor에 접근 가능하도록
	bool bIsActive;
};