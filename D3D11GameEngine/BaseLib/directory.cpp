#include "Pre.h"
#include "basefilesys.h"
#include <direct.h>
#include <filesystem>

base::directory::directory()
{
	to_current_dir();
	to_parent_dir();
}

base::directory::directory(const char* _path)
{
	path.copy(_path);
}

base::directory::directory(base::string& _path)
{
	path.copy(_path.c_str());
}

base::file base::directory::get_file(const char* _filename)
{
	std::filesystem::path spath = path.c_str();
	spath.append(_filename);
	if (!std::filesystem::exists(spath))
	{
		__debugbreak();
	}

	base::file file = spath.string().c_str();
	file.normalize();
	return file;
}

std::vector<base::file> base::directory::get_all_file()
{
	std::vector<base::file> result;
	result.reserve(100);
	for (auto& entry : std::filesystem::directory_iterator(path.c_str()))
	{
		auto& path = entry.path();
		if (std::filesystem::is_directory(path))
		{
			continue;
		}

		base::file file =  path.string().c_str();
		result.push_back(file);
	}

	return result;
}

std::vector<base::file> base::directory::get_all_file_ext(const char* _ext)
{
	std::vector<base::file> result;
	result.reserve(100);
	for (auto& entry : std::filesystem::directory_iterator(path.c_str()))
	{
		auto& path = entry.path();
		if (std::filesystem::is_directory(path))
		{
			continue;
		}

		if (_ext != path.extension())
		{
			continue;
		}
		base::file file = path.string().c_str();
		result.push_back(file);
	}

	return result;
}

void base::directory::to_current_dir()
{
	char cwd[1024];
	char* nullcheck = _getcwd(cwd, sizeof(cwd));
	if (nullcheck == nullptr)
	{
		__debugbreak();
	}
	path.copy(cwd);
}

void base::directory::to_parent_dir()
{
	std::filesystem::path spath = path.c_str();
	path.copy(spath.parent_path().string().c_str());
}

void base::directory::to_sub_dir(const char* _dir)
{
	std::filesystem::path spath = path.c_str();
	spath.append(_dir);

	if (!std::filesystem::exists(spath))
		__debugbreak();

	path.copy(spath.string().c_str());
}

void base::directory::normalize()
{
	char* head = (char*)path.c_str();
	while (*head != '\0')
	{
		if (*head == '\\')
		{
			*head = '/';
		}
		head++;
	}
}