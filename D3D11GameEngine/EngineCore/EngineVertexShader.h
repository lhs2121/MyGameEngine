#pragma once
#include "EngineD3DResource.h"

class EngineVertexShader : public EngineD3DResource<EngineVertexShader>
{
public:
	// constrcuter destructer
	EngineVertexShader();
	~EngineVertexShader();

	// delete Function
	EngineVertexShader(const EngineVertexShader& _Other) = delete;
	EngineVertexShader(EngineVertexShader&& _Other) noexcept = delete;
	EngineVertexShader& operator=(const EngineVertexShader& _Other) = delete;
	EngineVertexShader& operator=(EngineVertexShader&& _Other) noexcept = delete;

	void CreateResource(std::string _Name,std::string _Path);
	void IntoPipeLine() override;

	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();
private:
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;
};