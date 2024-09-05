#pragma once
#include "D3D11API.h"

class PixelShader : public IPixelShader
{
public:
	PixelShader();
	~PixelShader();

	void Setting(EngineString _Name, EngineString _Path) override;
	void IntoPipeline() override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
private:
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11PixelShader* ShaderPtr = nullptr;
};