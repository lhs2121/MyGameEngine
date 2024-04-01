#pragma once
#include "DirectResource.h"

class EnginePixelShader : public DirectResource<EnginePixelShader>
{
public:
	// constrcuter destructer
	EnginePixelShader();
	~EnginePixelShader();

	// delete Function
	EnginePixelShader(const EnginePixelShader& _Other) = delete;
	EnginePixelShader(EnginePixelShader&& _Other) noexcept = delete;
	EnginePixelShader& operator=(const EnginePixelShader& _Other) = delete;
	EnginePixelShader& operator=(EnginePixelShader&& _Other) noexcept = delete;

	void ShaderLoad(std::string _Name, std::string _Path);
	void IntoPipeLine() override;

private:
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11PixelShader* ShaderPtr = nullptr;
};