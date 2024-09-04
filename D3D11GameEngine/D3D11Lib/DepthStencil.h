#pragma once
#include "D3D11API.h"

class DepthStencil : public IDepthStencil
{
public:
	DepthStencil();
	~DepthStencil();

	void Setting(ID3D11Device* DevicePtr, D3D11_DEPTH_STENCIL_DESC _Desc) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr);
	ID3D11DepthStencilState* GetStatePtr() const { return StatePtr; }

private:
	D3D11_DEPTH_STENCIL_DESC Desc;
	ID3D11DepthStencilState* StatePtr;
};