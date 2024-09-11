#pragma once
#include <unordered_map>
#include "ResourceType.h"
#include <string>

template<class T>
class ResourceContainer
{
public:
	static T* Find(const char* _name);
	static std::unordered_map<std::string, T*> Resources;
};

template<class T>
std::unordered_map<std::string, T*> ResourceContainer<T>::Resources;

template<class T>
inline T* ResourceContainer<T>::Find(const char* _name)
{
	return Resources[_name];
}
