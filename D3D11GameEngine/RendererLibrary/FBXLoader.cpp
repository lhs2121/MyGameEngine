#include "pch.h"
#include "FBXLoader.h"

#pragma comment(lib,"libfbxsdk.lib")
void CFBXLoader::Initialize()
{
	m_pManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(m_pManager, IOSROOT);
	m_pManager->SetIOSettings(ios);

	FbxImporter* importer = FbxImporter::Create(m_pManager, "");
	importer->Initialize("desk.fbx", -1, m_pManager->GetIOSettings());
	const char* error = importer->GetStatus().GetErrorString();
		


	FbxScene* scene = FbxScene::Create(m_pManager, "scene");
	if (false == importer->Import(scene))
	{
		const char* error = importer->GetStatus().GetErrorString();
	}
	importer->Destroy();
	FbxNode* root = scene->GetRootNode();
	const char* name = root->GetName();
	if (root) 
	{
		for (int i = 0; i < root->GetChildCount(); i++)
		{
			FbxNode* node = root->GetChild(i);
			const char* name = node->GetName();
			int a = 0;
		}
	}
}
