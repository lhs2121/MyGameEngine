#pragma once
#include <vector>
constexpr int baseStrLen = 32;

namespace base
{
	class BaseAPI string
	{
	public:
		string();
		virtual ~string();

		string(const char* _other);
		string(const string& _other);
		
		void operator=(const string& _other);
		void operator=(const char* _other);

		void operator+=(const string& _other);
		void operator+=(const char* _other);
		void operator+=(int _other);
		void operator+=(float _other);

		bool operator==(const string& _other);
		bool operator==(const char* _other);

		bool operator!=(const string& _other);
		bool operator!=(const char* _other);

		bool operator<(const string& _other) const;
		bool operator<(const char* _other) const;

		bool operator>(const string& _other) const;
		bool operator>(const char* _other) const;

		void copy(const char* _other);

		const char* c_str();
		void w_str(wchar_t** ppwstr);

		int get_len() const;
		int get_int() const;
		double get_float() const;

	protected:
		char* str = nullptr;
	};

	class BaseAPI file
	{
	public:
		file();
		file(const char* _path);
		file(base::string& _path);

		const char* get_ext();
		base::string get_name();
		const char* get_name_and_ext();
		void normalize();

		base::string path;
	};

	class BaseAPI directory
	{
	public:
		directory();
		directory(const char* _path);
		directory(base::string& _path);

		base::file get_file(const char* _filename);
		std::vector<base::file> get_all_file();
		std::vector<base::file> get_all_file_ext(const char* _ext);

		void to_current_dir();
		void to_parent_dir();
		void to_sub_dir(const char* _dir);
		void normalize();

		base::string path;
	};
}