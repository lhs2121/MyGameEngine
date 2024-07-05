#pragma once
#include <queue>
#include "EngineBaseInterface.h"
class EngineStaticMemoryPool : public IEngineStaticMemoryPool
{
public:
	// constrcuter destructer
	EngineStaticMemoryPool();
	~EngineStaticMemoryPool();

	//constrcuter destructer
	EngineStaticMemoryPool(const EngineStaticMemoryPool& _Other) = delete;
	EngineStaticMemoryPool(EngineStaticMemoryPool&& _Other) noexcept = delete;
	EngineStaticMemoryPool& operator=(const EngineStaticMemoryPool& _Other) = delete;
	EngineStaticMemoryPool& operator=(EngineStaticMemoryPool&& _Other) noexcept = delete;

	void Init(int PoolSize, int _ObjectSize) override;
	void CleanUp() override;
	void* GetBlock() override;
	void FreeBlock(void* Ptr) override;

private:
	std::queue<void*> FreeBlocks;
	void* HeaderPtr = nullptr;
	void* NextPtr = nullptr;
	int ObjectSize = 0;
};

