#pragma once
#include <fbxsdk.h>

class CFBXLoader
{
public:
	void Initialize();
	FbxManager* m_pManager = nullptr;
};