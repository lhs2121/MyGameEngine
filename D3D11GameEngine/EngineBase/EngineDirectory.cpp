#include "Pre.h"
#include "EngineDirectory.h"
#include "EngineFile.h"
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

std::vector<EngineFile> EngineDirectory::GetAllFile()
{
	std::vector<EngineFile> AllFile;
	for (const std::filesystem::path& ele : std::filesystem::directory_iterator(Path))
	{
		if (std::filesystem::is_directory(ele))
		{
			continue;
		}

		EngineFile File(ele.string());
		AllFile.push_back(File);
    }
	return AllFile;
}

std::vector<EngineFile> EngineDirectory::GetAllFile(std::string _Ext)
{
	std::vector<EngineFile> AllFile;
	for (const std::filesystem::path& ele : std::filesystem::directory_iterator(Path))
	{
		if (std::filesystem::is_directory(ele))
		{
			continue;
		}

		std::string FileExt = ele.extension().string();
		if (FileExt != _Ext)
		{
			continue;
		}

		EngineFile File(ele.string());
		AllFile.push_back(File);
	}
	return AllFile;
}

