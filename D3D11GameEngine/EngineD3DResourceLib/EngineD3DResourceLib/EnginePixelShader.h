#pragma once
#include "IEngineD3D11.h"

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

	void Setting(EngineString _Name, EngineString _Path) override;
	void Release() override;
	void IntoPipeLine() override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}

	EngineDevice* DevicePtr;
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11PixelShader* ShaderPtr = nullptr;
};