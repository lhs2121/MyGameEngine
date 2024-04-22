#pragma once
#include "EngineD3DResource.h"

class EngineDepthStencil : public EngineD3DResource<EngineDepthStencil>
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
		return DepthStencilPtr;
	};
	void CreateResource(D3D11_DEPTH_STENCIL_DESC _Desc);
	void IntoPipeLine() override;

private:
	D3D11_DEPTH_STENCIL_DESC Desc;
	ID3D11DepthStencilState* DepthStencilPtr;
};