#pragma once
#include "D3D11API.h"

class PixelShader : public IPixelShader
{
public:
	PixelShader();
	~PixelShader();

	void Setting(ID3D11Device* DevicePtr, EngineString _Name, EngineString _Path) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr) override;

private:
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11PixelShader* ShaderPtr = nullptr;
};