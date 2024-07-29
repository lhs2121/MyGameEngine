#include "Pre.h"
#include "EngineMesh.h"
#include "EngineD3DManager.h"

UINT EngineMesh::GetIndexCount()
{
	return pIB->IndexCount;
}

void EngineMesh::Setting(const char* _VBName, const char* _IBName)
{
    pVB = (EngineVertexBuffer*)EngineD3DManager::MainManager->Find(ResType::VB, _VBName);
	pIB = (EngineIndexBuffer*)EngineD3DManager::MainManager->Find(ResType::IB, _IBName);
}

void EngineMesh::IntoPipeline()
{
	pVB->IntoPipeline();
	pIB->IntoPipeline();
}
