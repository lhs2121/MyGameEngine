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

	void Release() override;
	ID3D11DepthStencilState* GetResource()
	{
		return DepthStencil;
	};
	void IntoPipeLine();
	void SetDevicePtr(ID3D11DeviceContext* pDeviceContext)
	{
		DeviceContext = pDeviceContext;
	}
	ID3D11DeviceContext* DeviceContext;
	D3D11_DEPTH_STENCIL_DESC Desc;
	ID3D11DepthStencilState* DepthStencil;
};