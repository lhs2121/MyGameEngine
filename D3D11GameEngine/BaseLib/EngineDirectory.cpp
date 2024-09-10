#include "Pre.h"
#include "EngineDebug.h"
#include "EngineDirectory.h"
#include "EngineFile.h"
#include <iostream>
#include <filesystem>
#include <string>

EngineString EngineDirectory::BaseDir = "D3D11GameEngine";

EngineDirectory::EngineDirectory()
{
	Path = std::filesystem::current_path().string().c_str();
	GoBase();
}

void EngineDirectory::GoParent()
{	
	std::filesystem::path ParentPath = Path.c_str();
	if (true == std::filesystem::exists(ParentPath.parent_path()))
	{
		Path = ParentPath.parent_path().string().c_str();
	}
}

void EngineDirectory::GoChild(const char* ChildPath)
{
	std::filesystem::path TestPath = Path.c_str();
	TestPath /= ChildPath;

	if (true == std::filesystem::exists(TestPath))
	{
		Path = TestPath.string().c_str();
	}
}

void EngineDirectory::GoBase()
{
	while (true)
	{
		std::filesystem::path stdPath = Path.c_str();
		EngineString CurDir = stdPath.stem().string().c_str();

		if (CurDir == "")
		{
			EngineDebug::MsgBoxAssert("BaseDirectory를 찾을수없습니다");
		}
		if (EngineDirectory::BaseDir == CurDir.c_str())
		{
			Path = stdPath.string().c_str();
			break;
		}
		else
		{
			GoParent();
			continue;
		}
	
	}

}

EngineFile EngineDirectory::GetFile(const char* _name)
{
	std::filesystem::path stdPath = Path.c_str();
	if (_name != nullptr)
	{
		stdPath /= _name;
	}

	if (std::filesystem::exists(stdPath) == false)
	{
		EngineDebug::MsgBoxAssert("해당 파일이 없습니다");
	}

	Path = stdPath.string().c_str();
	Normalize();
	return EngineFile(Path.c_str());
}

std::vector<EngineFile> EngineDirectory::GetAllFile()
{
	std::vector<EngineFile> AllFile;

	std::filesystem::path DirPath = Path.c_str();

	for (const std::filesystem::path& Entry : std::filesystem::directory_iterator(DirPath))
	{
		if (std::filesystem::is_directory(Entry))
		{
			continue;
		}

		AllFile.emplace_back(Entry.string().c_str());
    }

	return AllFile;
}

std::vector<EngineFile> EngineDirectory::GetAllFileExt(const char* _Ext)
{
	std::vector<EngineFile> AllFile;

	std::filesystem::path DirPath = Path.c_str();

	for (const std::filesystem::path& Entry : std::filesystem::directory_iterator(DirPath))
	{
		if (std::filesystem::is_directory(Entry))
		{
			continue;
		}

		std::string FileExt = Entry.extension().string();
		if (FileExt != _Ext)
		{
			continue;
		}

		AllFile.emplace_back(Entry.string().c_str());
	}

	return AllFile;
}

void EngineDirectory::Normalize()
{
	char* c = (char*)Path.c_str();
	while (*c != '\0')
	{
		if (*c == '\\')
		{
			*c = '/';
		}
		c++;
	}
}

