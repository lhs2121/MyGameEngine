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

	void SetResource();
	void IntoPipeLine() override;

private:
	void* Bytecode;
	SIZE_T BytecodeLength;
	ID3D11ClassLinkage* pClassLinkage;
	ID3D11VertexShader* ShaderPtr = nullptr;
};