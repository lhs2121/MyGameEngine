#include "Pre.h"
#include "Mesh.h"
#include "ResManager.h"

UINT Mesh::GetIndexCount()
{
	return pIB->IndexCount;
}

IVertexBuffer* Mesh::GetVB()
{
	return pVB;
}

void Mesh::Setting(const char* _VBName, const char* _IBName)
{
    pVB = (VertexBuffer*)ManagerPtr->Find(ResType::VB, _VBName);
	pIB = (IndexBuffer*)ManagerPtr->Find(ResType::IB, _IBName);
}

void Mesh::IntoPipeline()
{
	pVB->IntoPipeline(ContextPtr);
	pIB->IntoPipeline(ContextPtr);
}
