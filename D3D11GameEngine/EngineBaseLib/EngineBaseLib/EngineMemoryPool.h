#pragma once

class __declspec(dllexport) EngineMemoryPool
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

	void Allocate(int Byte);

private:
	void* curptr;
	void* nextptr;
};

