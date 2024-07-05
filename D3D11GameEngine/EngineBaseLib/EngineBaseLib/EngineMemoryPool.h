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

	void   Init(int PoolSize) override;
	void   CleanUp() override;
	void* GetBlock(int _Size) override;
	void   FreeBlock(void* Ptr) override;


private:
	int SizeSearch(int Size);
	std::queue<void*> FreeBlocks;
	void* InitPtr = nullptr;
	void* HeaderPtr = nullptr;
	void* FreePtr = nullptr;
};

