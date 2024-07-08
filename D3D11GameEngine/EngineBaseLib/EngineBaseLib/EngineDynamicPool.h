#pragma once
#include <queue>
#include "IEngineBase.h"
class EngineDynamicPool : public IEngineDynamicPool
{
public:
	// constrcuter destructer
	EngineDynamicPool();
	~EngineDynamicPool();

	//constrcuter destructer
	EngineDynamicPool(const EngineDynamicPool& _Other) = delete;
	EngineDynamicPool(EngineDynamicPool&& _Other) noexcept = delete;
	EngineDynamicPool& operator=(const EngineDynamicPool& _Other) = delete;
	EngineDynamicPool& operator=(EngineDynamicPool&& _Other) noexcept = delete;

	void  Init(int PoolSize) override;
	void  CleanUp() override;
	void* GetBlock(int _Size) override;
	void  FreeBlock(void* Ptr) override;


private:
	int SizeSearch(int Size);
	std::queue<void*> FreeBlocks;
	void* InitPtr = nullptr;
	void* HeaderPtr = nullptr;
	void* FreePtr = nullptr;
};

