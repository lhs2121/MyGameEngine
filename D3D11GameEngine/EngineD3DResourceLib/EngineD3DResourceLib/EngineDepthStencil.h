#pragma once
#include "IEngineD3DRes.h"

class EngineDepthStencil : public IEngineDepthStencil
{
public:
	// constrcuter destructer
	EngineDepthStencil();
	~EngineDepthStencil();

	// delete Function
	EngineDepthStencil(const EngineDepthStencil& _Other) = delete;
	EngineDepthStencil(EngineDepthStencil&& _Other) noexcept = delete;
	EngineDepthStencil& operator=(const EngineDepthStencil& _Other) = delete;
	EngineDepthStencil& operator=(EngineDepthStencil&& _Other) noexcept = delete;

	ID3D11DepthStencilState* GetResource()
	{
		return m_pDepthStencil;
	};
	void IntoPipeLine();
	void SetDevicePtr(IEngineDevice* pDevice)
	{
		Device = pDevice;
	}

	IEngineDevice* Device;
	D3D11_DEPTH_STENCIL_DESC m_Desc;
	ID3D11DepthStencilState* m_pDepthStencil;
};