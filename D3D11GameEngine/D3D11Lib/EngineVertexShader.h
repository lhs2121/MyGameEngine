#pragma once
#include "D3D11API.h"

class EngineVertexShader : public IEngineVertexShader
{
public:
	EngineVertexShader();
	~EngineVertexShader();

	std::vector<EngineString>  GetSementics() { return Sementics; }
	UINT GetSlotNumber(const char* _BindingResName);

	void Setting(EngineString _Name, EngineString _Path) override;
	void IntoPipeline() override;
	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	ID3DBlob* BlobPtr = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;

	EngineFile           ShaderFile;
	std::vector<EngineString>  Sementics;
};