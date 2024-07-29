#pragma once
#include "D3D11API.h"

class EnginePixelShader : public IEnginePixelShader
{
public:
	EnginePixelShader();
	~EnginePixelShader();

	void Setting(EngineString _Name, EngineString _Path) override;
	void IntoPipeline() override;

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11PixelShader* ShaderPtr = nullptr;
};