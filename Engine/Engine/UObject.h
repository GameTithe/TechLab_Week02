#pragma once
typedef unsigned int uint32;
class UObject {
public:
	uint32 UUID;
	uint32 InternalIndex; // Index of GUObjectArray
protected: // public °í¹Î
	UObject() {}
	virtual ~UObject() {}
};