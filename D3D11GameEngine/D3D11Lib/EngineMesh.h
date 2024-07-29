#pragma once
#include "D3D11API.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"

class EngineMesh : public IMesh
{
public:
	void Setting(const char* _VBName, const char* _IBName) override;
	void IntoPipeline() override;

	UINT GetIndexCount() override;

private:
	EngineVertexBuffer* pVB = nullptr;
	EngineIndexBuffer* pIB = nullptr;
};