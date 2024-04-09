#pragma once
#include "EnginePath.h"

class EngineFile;
class EngineDirectory : public EnginePath
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

	void ParentDir();
	void ChildDir(std::string ChildPath);

	std::vector<EngineFile> GetAllFile();
	std::vector<EngineFile> GetAllFile(std::string _Ext);
};

