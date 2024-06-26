#pragma once
#include "EngineString.h"

class EngineAPI EngineDirectory
{
public:
	// constrcuter destructer
	EngineDirectory();
	~EngineDirectory();

	// constrcuter destructer
	EngineDirectory(const EngineDirectory& _Other) = delete;
	EngineDirectory(EngineDirectory&& _Other) noexcept = delete;
	EngineDirectory& operator=(const EngineDirectory& _Other) = delete;
	EngineDirectory& operator=(EngineDirectory&& _Other) noexcept = delete;

	void GoParent();
	void GoChild(const char* ChildPath);
	void GoBase();

	void GetAllFile(void* vector);
	void GetAllFileExt(void* vector, const char* _Ext);

private:
	static EngineString BaseDir;
	EngineString Path;
};

