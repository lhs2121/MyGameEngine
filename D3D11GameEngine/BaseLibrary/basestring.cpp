#include "pch.h"
#include "basestring.h"
#include <direct.h>
#include <filesystem>

base::string::string()
{
}

base::string::~string()
{
	if (str)
	{
		free(str);
		str = nullptr;
	}
}

base::string::string(const char* __other)
{
	copy(__other);
}

base::string::string(const string& __other)
{
	copy(__other.str);
}

void base::string::operator=(const string& __other)
{
	copy(__other.str);
}

void base::string::operator=(const char* __other)
{
	copy(__other);
}

void base::string::operator+=(const string& __other)
{
	*this += __other.str;
}

void base::string::operator+=(const char* __other)
{
	int size = get_len();
	int _othersize = (int)strlen(__other) + 1;

	if (1024 < size + _othersize)
	{
		__debugbreak();
	}

	char result[1024];

	memcpy_s(result, size, str, size);
	memcpy_s(&result[size], _othersize, __other, _othersize);

	copy(result);
}

void base::string::operator+=(int __other)
{
	char result[11];
	snprintf(result, 11, "%d", __other);

	*this += result;
}

void base::string::operator+=(float __other)
{
	char result[128];
	snprintf(result, 128, "%f", __other);

	*this += result;
}

bool base::string::operator==(const string& __other)
{
	return *this == __other.str;
}

bool base::string::operator==(const char* __other)
{
	if (0 == strcmp(str, __other))
	{
		return true;
	}

	return false;
}

bool base::string::operator!=(const string& __other)
{
	return *this != __other.str;
}

bool base::string::operator!=(const char* __other)
{
	if (0 != strcmp(str, __other))
	{
		return true;
	}

	return false;
}

bool base::string::operator<(const string& __other) const
{
	return *this < __other.str;
}

bool base::string::operator<(const char* __other) const
{
	int r = strcmp(str, __other);
	if (r < 0)
	{
		return true;
	}
	return false;
}

bool base::string::operator>(const string& __other) const
{
	return *this > __other.str;
}

bool base::string::operator>(const char* __other) const
{
	int r = strcmp(str, __other);
	if (r > 0)
	{
		return true;
	}
	return false;
}

void base::string::copy(const char* __other)
{
	if (__other == nullptr)
	{
		str = nullptr;
		return;
	}

	int newlen = baseStrLen;
	int len = (int)strlen(__other) + 1;

	if (len > newlen)
		newlen = len;

	if (str != nullptr)
	{
		if (len <= baseStrLen)
		{
			memset(str, 0, newlen);
		}
		else
		{
			str = (char*)realloc(str, newlen);
		}
	}
	else
	{
     	str = (char*)malloc(newlen);
	}

	errno_t e = strcpy_s(str, len, __other);
	if (e != 0)
	{
		__debugbreak();
	}
}

void base::string::w_str(wchar_t** ppwstr)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	*ppwstr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, *ppwstr, len);
}

const char* base::string::c_str()
{
	return (const char*)str;
}

int base::string::get_len() const
{
	if (str == nullptr)
	{
		return 0;
	}

	return (int)strlen(str);
}

int base::string::get_int() const
{
	return atoi(str);
}

double base::string::get_float() const
{
	return atof(str);
}

base::string base::string::get_file(const char* _filename)
{
	std::filesystem::path szPath = str;
	szPath.append(_filename);
	if (!std::filesystem::exists(szPath))
	{
		__debugbreak();
	}

	base::string sz_file = szPath.string().c_str();
	sz_file.normalize();
	return sz_file;
}

std::vector<base::string> base::string::get_all_file()
{
	std::vector<base::string> result;
	result.reserve(100);
	for (auto& entry : std::filesystem::directory_iterator(str))
	{
		auto& path = entry.path();
		if (std::filesystem::is_directory(path))
		{
			continue;
		}

		base::string szFile = path.string().c_str();
		result.push_back(szFile);
	}

	return result;
}

std::vector<base::string> base::string::get_all_file_ext(const char* _ext)
{
	std::vector<base::string> result;
	result.reserve(100);
	for (auto& entry : std::filesystem::directory_iterator(str))
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
		base::string file = path.string().c_str();
		result.push_back(file);
	}

	return result;
}


void base::string::to_current_dir()
{
	char cwd[1024];
	char* nullcheck = _getcwd(cwd, sizeof(cwd));
	if (nullcheck == nullptr)
	{
		__debugbreak();
	}
	copy(cwd);

	to_parent_dir();
}

void base::string::to_parent_dir()
{
	std::filesystem::path path = str;
	copy(path.parent_path().string().c_str());
}

void base::string::to_sub_dir(const char* _dir)
{
	std::filesystem::path path = str;
	path.append(_dir);

	if (!std::filesystem::exists(path))
		__debugbreak();

	copy(path.string().c_str());
}

void base::string::normalize()
{
	char* head = (char*)str;
	while (*head != '\0')
	{
		if (*head == '\\')
		{
			*head = '/';
		}
		head++;
	}
}

const char* base::string::get_ext()
{
	char* tail = (char*)str;
	tail += get_len();
	while (true)
	{
		tail--;
		if (*tail == '.')
		{
			return tail;
		}

		if (tail == str)
		{
			__debugbreak();
		}
	}
}

base::string base::string::get_name()
{
	char* name_ext = (char*)get_name_and_ext();
	char buffer[64];
	int len = (int)strlen(name_ext) + 1;
	memcpy_s(buffer, len, name_ext, len);

	char* tail = &buffer[len];

	while (*tail != '.')
	{
		*tail = '\0';
		tail--;
	}
	*tail = '\0';

	base::string result = buffer;
	return result;

}

const char* base::string::get_name_and_ext()
{
	char* tail = (char*)str;
	tail += get_len();
	while (true)
	{
		tail--;
		if (*tail == '\\' || *tail == '/')
		{
			tail++;
			return tail;
		}
		if (tail == str)
		{
			__debugbreak();
		}
	}
}