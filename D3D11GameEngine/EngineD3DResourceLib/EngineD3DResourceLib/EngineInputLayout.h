#pragma once
#include "IEngineD3DRes.h"

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

	void IntoPipeLine() override;
	void SetDevicePtr(IEngineDevice* pDevice)
	{
		pDevice = pDevice;
	}
	IEngineDevice* m_pDevice;
	UINT ElementNum = 0;
	D3D11_INPUT_ELEMENT_DESC* LayoutDesc;
	ID3D11InputLayout* LayoutPtr;
};