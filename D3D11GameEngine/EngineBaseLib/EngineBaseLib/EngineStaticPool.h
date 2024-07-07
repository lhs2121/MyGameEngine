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

	void Init(int _BlockCount, int _BlockSize) override;
	void CleanUp() override;
	void* GetBlock() override;
	void FreeBlock(void* Ptr) override;

private:
	std::list<void*> FreeBlocks;

	void* HeaderArray = nullptr;
	void* InitPtr = nullptr;
	void* HeaderPtr = nullptr;
	int BlockSize = 0;
};

