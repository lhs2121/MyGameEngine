#include "Pre.h"
#include "basefilesys.h"

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

base::string::string(const char* _other)
{
	copy(_other);
}

base::string::string(const string& _other)
{
	copy(_other.str);
}
void base::string::operator=(const string& _other)
{
	copy(_other.str);
}

void base::string::operator=(const char* _other)
{
	copy(_other);
}

void base::string::operator+=(const string& _other)
{
	*this += _other.str;
}

void base::string::operator+=(const char* _other)
{
	int size = get_len();
	int othersize = (int)strlen(_other) + 1;

	if (1024 < size + othersize)
	{
		__debugbreak();
	}

	char result[1024];

	memcpy_s(result, size, str, size);
	memcpy_s(&result[size], othersize, _other, othersize);

	copy(result);
}

void base::string::operator+=(int _other)
{
	char result[11];
	snprintf(result, 11, "%d", _other);

	*this += result;
}

void base::string::operator+=(float _other)
{
	char result[128];
	snprintf(result, 128, "%f", _other);

	*this += result;
}

bool base::string::operator==(const string& _other)
{
	return *this == _other.str;
}

bool base::string::operator==(const char* _other)
{
	if (0 == strcmp(str, _other))
	{
		return true;
	}

	return false;
}

bool base::string::operator!=(const string& _other)
{
	return *this != _other.str;
}

bool base::string::operator!=(const char* _other)
{
	if (0 != strcmp(str, _other))
	{
		return true;
	}

	return false;
}

bool base::string::operator<(const string& _other) const
{
	return *this < _other.str;
}

bool base::string::operator<(const char* _other) const
{
	int r = strcmp(str, _other);
	if (r < 0)
	{
		return true;
	}
	return false;
}

bool base::string::operator>(const string& _other) const
{
	return *this > _other.str;
}

bool base::string::operator>(const char* _other) const
{
	int r = strcmp(str, _other);
	if (r > 0)
	{
		return true;
	}
	return false;
}

void base::string::copy(const char* _other)
{
	if (_other == nullptr)
	{
		str = nullptr;
		return;
	}

	int newlen = baseStrLen;
	size_t len = strlen(_other) + 1;

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

	errno_t e = strcpy_s(str, len, _other);
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

