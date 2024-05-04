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

	void Release() override;
	void IntoPipeLine() override;
	void* GetShaderByteCode();
	SIZE_T GetShaderByteLength();
	void SetDevicePtr(ID3D11DeviceContext* pDeviceContext)
	{
		DeviceContext = pDeviceContext;
	}
	ID3D11DeviceContext* DeviceContext;
	ID3DBlob* ShaderBlob = nullptr;
	ID3D11VertexShader* ShaderPtr = nullptr;
};