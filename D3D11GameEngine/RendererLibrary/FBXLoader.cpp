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
	std::vector<int> indexList;
	for (int i = 0; i < count; i++)
	{
		FbxNode* pNode = pRoot->GetChild(i);
		FbxMesh* pMesh = pNode->GetMesh();
		if (pMesh != nullptr)
		{
			int vertexCount = pMesh->GetPolygonCount();
			pVertexList = pMesh->GetControlPoints();

			int polCount = pMesh->GetPolygonCount();
			for (int i = 0; i < polCount; i++)
			{
				int polSize = pMesh->GetPolygonSize(i);
				for (int j = 0; j < polSize; j++)
				{
					int index = pMesh->GetPolygonVertex(i, j);
					indexList.push_back(index);
				}

			}
			if (pVertexList != nullptr)
			{
				m_pRenderer->CreateMesh("ribbon", pVertexList, sizeof(FbxVector4) * vertexCount, sizeof(FbxVector4), &indexList[0], sizeof(int) * indexList.size(), sizeof(int));
			}

		}
	}
}
