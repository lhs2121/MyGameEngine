#pragma once
#include <queue>
#include "IEngineBase.h"

struct FreeQueue
{
	~FreeQueue();
	void Init(int _PtrCount);
	bool Empty();
	void Push(void* _Ptr);
	void* Pop();

	int PtrCount = 0;
	int LastIndex = 0;
	void** PtrArray = nullptr;
};
class EngineStaticPool : public IEngineStaticPool
{
public:
	// constrcuter destructer
	EngineStaticPool();
	~EngineStaticPool();

	//constrcuter destructer
	EngineStaticPool(const EngineStaticPool& _Other) = delete;
	EngineStaticPool(EngineStaticPool&& _Other) noexcept = delete;
	EngineStaticPool& operator=(const EngineStaticPool& _Other) = delete;
	EngineStaticPool& operator=(EngineStaticPool&& _Other) noexcept = delete;

	void Init(int _BlockCount, int _BlockSize) override;
	void CleanUp() override;
	void* GetBlock() override;
	void FreeBlock(void* Ptr) override;

private:
	
	FreeQueue Queue;

	void* HeaderArray = nullptr;
	void* InitPtr = nullptr;
	void* HeaderPtr = nullptr;
	int BlockCount = 0;
	int BlockSize = 0;
};
