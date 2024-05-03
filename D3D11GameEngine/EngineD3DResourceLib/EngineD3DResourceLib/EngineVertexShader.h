#pragma once
#include "IEngineD3DRes.h"

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

	void IntoPipeLine() override;
	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();
	void SetDevicePtr(IEngineDevice* pDevice)
	{
		Device = pDevice;
	}
	IEngineDevice* Device;
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;
};