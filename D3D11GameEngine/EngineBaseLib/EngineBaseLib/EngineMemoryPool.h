#pragma once
#include <queue>
#include "EngineBaseInterface.h"
class EngineMemoryPool : public IEngineMemoryPool
{
public:
	// constrcuter destructer
	EngineMemoryPool();
	~EngineMemoryPool();

	//constrcuter destructer
	EngineMemoryPool(const EngineMemoryPool& _Other) = delete;
	EngineMemoryPool(EngineMemoryPool&& _Other) noexcept = delete;
	EngineMemoryPool& operator=(const EngineMemoryPool& _Other) = delete;
	EngineMemoryPool& operator=(EngineMemoryPool&& _Other) noexcept = delete;

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

