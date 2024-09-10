#pragma once
#include <unordered_map>

template<class T>
class ResourceContainer
{
public:
	static std::unordered_map<const char*, T*> Resources;
};

template<class T>
std::unordered_map<const char*, T*> ResourceContainer<T>::Resources;