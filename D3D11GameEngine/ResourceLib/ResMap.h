#pragma once
#include <unordered_map>
#include "ResourceType.h"
#include <string>

template<class T>
class ResMap
{
public:
	static T* Find(const char* _name);
	static std::unordered_map<std::string, T*> map;
};

template<class T>
std::unordered_map<std::string, T*> ResMap<T>::map;

template<class T>
inline T* ResMap<T>::Find(const char* _name)
{
	if (map.find(_name) == map.end())
	{
		return nullptr;
	}
	return map[_name];
}
