#pragma once
#include <filesystem>

class __declspec(dllexport) EnginePath
{
public:
	// constrcuter destructer
	EnginePath();
	EnginePath(std::string _Path);

	~EnginePath();

	// constrcuter destructer
	//EnginePath(const EnginePath& _Other) = delete;
	//EnginePath(EnginePath&& _Other) noexcept = delete;
	//EnginePath& operator=(const EnginePath& _Other) = delete;
	//EnginePath& operator=(EnginePath&& _Other) noexcept = delete;

	std::string GetStringPath();

protected:
	std::filesystem::path Path;
};

