#include "pch.h"
#include "FBXLoader.h"
#include "Renderer.h"
#include <vector>

#pragma comment(lib,"libfbxsdk.lib")
void CFBXLoader::Initialize(CRenderer* pRenderer)
{
	m_pRenderer = pRenderer;
	m_pManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(m_pManager, IOSROOT);
	m_pManager->SetIOSettings(ios);

	FbxImporter* importer = FbxImporter::Create(m_pManager, "");
	if (false == importer->Initialize("ribbon.fbx", -1, m_pManager->GetIOSettings()))
	{
		const char* error = importer->GetStatus().GetErrorString();
		__debugbreak();
	}

	FbxScene* scene = FbxScene::Create(m_pManager, "scene");
	if (false == importer->Import(scene))
	{
		const char* error = importer->GetStatus().GetErrorString();
		__debugbreak();
	}

	LoadMesh(scene);
	importer->Destroy();
}

void CFBXLoader::LoadMesh(FbxScene* pScene)
{
	FbxNode* pRoot = pScene->GetRootNode();
	FbxMesh* pMesh = pRoot->GetMesh();
	if (pMesh != nullptr)
	{
		int a = 0;
	}
	int count = pRoot->GetChildCount();
	FbxVector4* pVertexList = nullptr;
	for (int i = 0; i < count; i++)
	{
		FbxNode* pNode = pRoot->GetChild(i);
		FbxMesh* pMesh = pNode->GetMesh();
		if (pMesh != nullptr)
		{
			int vertexCount = pMesh->GetPolygonCount();
			pVertexList = pMesh->GetControlPoints();
			if (pVertcies != nullptr)
			{
				m_pRenderer->CreateMesh("newmesh",pVertcies,sizeof(FbxVector4)* vertexCount,sizeof(FbxVector4),)
			}

		}
	}
}
