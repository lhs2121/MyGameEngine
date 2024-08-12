#pragma once
#include "D3D11API.h"

struct SementicInfo
{
	EngineString SementicName;
	UINT InputSlot = 0;
};

class EngineVertexShader : public IEngineVertexShader
{
public:
	EngineVertexShader();
	~EngineVertexShader();

	UINT GetSementicCount() { return SementicCount; }
	SementicInfo* SetSementicInfo();
	SementicInfo* GetSementicInfo() { return InfoArray; }
	void Setting(EngineString _Name, EngineString _Path) override;
	void IntoPipeline() override;
	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device*        DevicePtr  = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	ID3DBlob*            BlobPtr = nullptr;
	ID3D11VertexShader*  ShaderPtr  = nullptr;

	EngineString         Path;

	SementicInfo*        InfoArray = nullptr;
	UINT                 SementicCount = 0;
};