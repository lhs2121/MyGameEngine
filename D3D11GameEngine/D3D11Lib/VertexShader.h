#pragma once
#include "D3D11API.h"

class VertexShader : public IVertexShader
{
public:
	VertexShader();
	~VertexShader();

	std::vector<EngineString>  GetSementics() { return Sementics; }
	EngineString GetLayoutName();
	UINT GetSlotNumber(const char* _BindingResName);

	void Setting(ID3D11Device* DevicePtr, EngineString _Name, EngineString _Path) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr) override;
	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();

private:
	ID3DBlob* BlobPtr = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;
	EngineFile           ShaderFile;
	std::vector<EngineString>  Sementics;
};