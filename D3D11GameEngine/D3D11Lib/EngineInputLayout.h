#pragma once
#include "D3D11API.h"

class EngineInputLayout : public IEngineInputLayout
{
public:
	// constrcuter destructer
	EngineInputLayout();
	~EngineInputLayout();

	// delete Function
	EngineInputLayout(const EngineInputLayout& _Other) = delete;
	EngineInputLayout(EngineInputLayout&& _Other) noexcept = delete;
	EngineInputLayout& operator=(const EngineInputLayout& _Other) = delete;
	EngineInputLayout& operator=(EngineInputLayout&& _Other) noexcept = delete;

	void Setting(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _ElementNum, void* ShaderBytecode, SIZE_T BytecodeLength) override;
	void Release() override;
	void IntoPipeLine() override;
	void SetDevicePtr(EngineDevice* _DevicePtr)
	{
		DevicePtr = _DevicePtr;
	}

	EngineDevice* DevicePtr;
	D3D11_INPUT_ELEMENT_DESC* Desc;
	ID3D11InputLayout* LayoutPtr;
};