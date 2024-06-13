#pragma once
#pragma warning(disable:4099)
#include "DLLCommon.h"

enum class FileMode;
struct IEngineMemoryPool
{ 	      
	virtual void  Init(int PoolSize, int _ObjectSize) = 0;
	virtual void  CleanUp() = 0;	    	      
	virtual void* GetBlock() = 0;
	virtual void  FreeBlock(void* Ptr) = 0;
};

struct IEngineFile
{
	virtual void SetPath(const char* _Path) = 0;
	virtual const char* GetFileName() = 0;
	virtual void Open(FileMode _Mode) = 0;
	virtual void Close() = 0;
};

struct IEngineDirectory
{
	virtual void GoParent() = 0;
	virtual void GoChild(const char* ChildPath) = 0;
	virtual void GoBase() = 0;
	
	virtual void GetAllFile(void* std_vector_IEngineFile) = 0;
	virtual void GetAllFileExt(void* std_vector_IEngineFile, const char* _Ext) = 0;
};

extern "C" EngineAPI void CreateMemoryPool(IEngineMemoryPool** ppMemoryPool);
extern "C" EngineAPI void CreateDir(IEngineDirectory** ppDirectory);