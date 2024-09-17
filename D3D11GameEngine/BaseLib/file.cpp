#include "Pre.h"
#include "basefilesys.h"

base::file::file()
{
}

base::file::file(const char* _path)
{
	path.copy(_path);
}

base::file::file(base::string& _path)
{
	path.copy(_path.c_str());
}

const char* base::file::get_ext()
{
	char* tail = (char*)path.c_str();
	tail += path.get_len();
	while (true)
	{
		tail--;
		if (*tail == '.')
		{
			return tail;
		}

		if (tail == path.c_str())
		{
			__debugbreak();
		}
	}
}

base::string base::file::get_name()
{
	char* name_ext = (char* )get_name_and_ext();
	char buffer[64];
	int len = (int)strlen(name_ext) + 1;
	memcpy_s(buffer,len, name_ext,len);

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

const char* base::file::get_name_and_ext()
{
	char* tail = (char*)path.c_str();
	tail += path.get_len();
	while (true)
	{
		tail--;
		if (*tail == '\\' || *tail == '/')
		{
			tail++;
			return tail;
		}
		if (tail == path.c_str())
		{
			__debugbreak();
		}
	}
}

void base::file::normalize()
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