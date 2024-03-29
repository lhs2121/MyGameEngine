#pragma once
#include <filesystem>

class EngineDirectory
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
	std::string GetStringPath();
	std::vector<std::string> GetAllFilePath();
	std::filesystem::path Path;
};

