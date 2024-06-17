#pragma once
#include "EngineD3DInterface.h"

class EngineVertexShader : public IEngineVertexShader
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

	void Setting(EngineString _Name, EngineString _Path) override;
	void Release() override;
	void IntoPipeLine() override;
	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}

	EngineDevice* DevicePtr;
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;
};