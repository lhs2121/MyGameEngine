#include "Pre.h"
#include "EngineDirectory.h"
#include <iostream>

EngineDirectory::EngineDirectory()
{
	Path = std::filesystem::current_path();
}

EngineDirectory::~EngineDirectory()
{
}

void EngineDirectory::ParentDir()
{	
	std::filesystem::path ParentPath;
	if (true == std::filesystem::exists(Path.parent_path()))
	{
		Path = Path.parent_path();
	}
}

void EngineDirectory::ChildDir(std::string ChildPath)
{
	std::filesystem::path TestPath = Path;
	TestPath /= ChildPath;

	if (true == std::filesystem::exists(TestPath))
	{
		Path /= ChildPath;
	}
}

std::string EngineDirectory::GetStringPath()
{
	std::string StringPath = Path.string();
	return StringPath;
}

std::vector<std::string> EngineDirectory::GetAllFilePath()
{
	std::vector<std::string> AllFile;
	for (const std::filesystem::path& ele : std::filesystem::directory_iterator(Path))
	{
		if (std::filesystem::is_directory(ele))
		{
			continue;
		}
		std::string FilePath = ele.string();
		AllFile.push_back(FilePath);
    }
	return AllFile;
}

