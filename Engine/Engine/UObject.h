#pragma once
#include "Typedef.h"
class UObject {
private:
	uint32 UUID;
	uint32 InternalIndex; // Index of GUObjectArray

	static TArray<UObject*> GUObjectArray;
protected: // public 고민
	UObject() 
	{
		static int CurUUID = 1;
		UUID = CurUUID++;
		InternalIndex = UObjectArrayPush(this);
	}
	virtual ~UObject() 
	{
		UOBjectArrayPop(InternalIndex);
	}
public:
	uint32 GetUUID()
	{
		return UUID;
	}

	static UObject* FindObject(uint32 uuid)
	{
		for(UObject* object : GUObjectArray)
		{
			if(object->UUID == uuid)
			{
				return object;
			}
		}
		return nullptr;
	}

private:
	static uint32 UObjectArrayPush(UObject* uobject)
	{
		int uObjCount = GUObjectArray.size();

		for(int i=0;i<uObjCount;i++)
		{
			if(GUObjectArray[i] == nullptr)
			{
				GUObjectArray[i] = uobject;
				return i;
			}
		}

		GUObjectArray.push_back(uobject);
		return uObjCount;
	}

	static void UOBjectArrayPop(uint32 idx)
	{
		GUObjectArray[idx] = nullptr;
	}
	
}; 