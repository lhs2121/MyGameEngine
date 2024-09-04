#pragma once
#include "D3D11API.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh : public IMesh
{
public:
	void Setting(const char* _VBName, const char* _IBName) override;
	void IntoPipeline() override;

	UINT GetIndexCount() override;
    IVertexBuffer* GetVB() override;

	ID3D11DeviceContext* ContextPtr = nullptr;
	IResManager* ManagerPtr = nullptr;
private:
	VertexBuffer* pVB = nullptr;
	IndexBuffer* pIB = nullptr;
};