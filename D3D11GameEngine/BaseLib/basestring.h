#pragma once
#include <vector>
constexpr int baseStrLen = 32;

namespace base
{
	class BaseAPI string
	{
	public:
		string();
		~string();

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

		//directory
		base::string get_file(const char* _filename);
		std::vector<base::string> get_all_file();
		std::vector<base::string> get_all_file_ext(const char* _ext);

		void to_current_dir();
		void to_parent_dir();
		void to_sub_dir(const char* _dir);
		void normalize();

		//file
		const char* get_ext();
		base::string get_name();
		const char* get_name_and_ext();

	protected:
		char* str = nullptr;
	};
}