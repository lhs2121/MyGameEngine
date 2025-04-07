#pragma once
#include <fbxsdk.h>

class Renderer;
class FBXLoader
{
public:
	void Initialize(Renderer* pRenderer);
	void LoadMesh(FbxScene* pScene);
	void LoadMaterial(FbxScene* pScene);
	FbxManager* m_pManager = nullptr;
	Renderer* m_pRenderer = nullptr;
};