#pragma once
#include <queue>
#include "EngineBaseInterface.h"

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

