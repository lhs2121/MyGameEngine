#pragma once
#include "EngineString.h"

class EngineDirectory : public IEngineDirectory
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

	void GoParent() override;
	void GoChild(const char* ChildPath) override;
	void GoBase() override;

	void GetAllFile(void* vector) override;
	void GetAllFileExt(void* vector, const char* _Ext) override;

private:
	static EngineString BaseDir;
	EngineString Path;
};

