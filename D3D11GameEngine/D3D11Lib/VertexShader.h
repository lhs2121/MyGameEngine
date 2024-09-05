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

	void Setting(EngineString _Name, EngineString _Path) override;
	void IntoPipeline() override;
	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
private:
	ID3DBlob* BlobPtr = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;
	EngineFile           ShaderFile;
	std::vector<EngineString>  Sementics;
};