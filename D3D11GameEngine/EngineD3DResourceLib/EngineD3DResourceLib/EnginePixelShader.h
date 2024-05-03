#pragma once
#include "IEngineD3DRes.h"

class EnginePixelShader : public IEnginePixelShader
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

	void IntoPipeLine() override;
	void SetDevicePtr(IEngineDevice* pDevice)
	{
		Device = pDevice;
	}
	IEngineDevice* Device;
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11PixelShader* ShaderPtr = nullptr;
};