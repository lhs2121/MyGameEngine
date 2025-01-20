#pragma once
#include <fbxsdk.h>

class CRenderer;
class CFBXLoader
{
public:
	void Initialize(CRenderer* pRenderer);
	void LoadMesh(FbxScene* pScene);
	FbxManager* m_pManager = nullptr;
	CRenderer* m_pRenderer = nullptr;
};