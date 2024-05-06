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

	void Release() override;
	void IntoPipeLine() override;
	void SetDevicePtr(ID3D11DeviceContext* pDeviceContext)
	{
		DeviceContext = pDeviceContext;
	}
	ID3D11DeviceContext* DeviceContext;
	D3D11_INPUT_ELEMENT_DESC* Desc;
	ID3D11InputLayout* LayoutPtr;
};