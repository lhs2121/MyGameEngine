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

	void CreatePool(int PoolSize,int _ObjectSize);
	void DeletePool();

	void* InsertObject(void* Ptr);
	void DeleteObject(void* Ptr);

private:
	void* HeaderPtr = nullptr;
	void* NextPtr = nullptr;
	int ObjectSize = 0;
};

