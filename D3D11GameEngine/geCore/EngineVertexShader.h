#pragma once
#include "DirectResource.h"

class EngineVertexShader : public DirectResource<EngineVertexShader>
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

	void ShaderLoad(std::string _Name,std::string _Path);
	void IntoPipeLine() override;

	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();
private:
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;
};