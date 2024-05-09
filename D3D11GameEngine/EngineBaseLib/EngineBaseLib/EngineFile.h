#pragma once
#include "EnginePath.h"

class __declspec(dllexport) EngineFile : public EnginePath
{
public:
	// constrcuter destructer
	EngineFile();
	EngineFile(std::string _Path);
	~EngineFile();

	// constrcuter destructer
	//EngineFile(const EngineFile& _Other) = delete;
	//EngineFile(EngineFile&& _Other) noexcept = delete;
	//EngineFile& operator=(const EngineFile& _Other) = delete;
	//EngineFile& operator=(EngineFile&& _Other) noexcept = delete;

	std::string GetFileName();
};

