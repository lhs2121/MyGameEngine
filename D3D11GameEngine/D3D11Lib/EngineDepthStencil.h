#pragma once
#include "D3D11API.h"

class EngineDepthStencil : public IEngineDepthStencil
{
public:
	EngineDepthStencil();
	~EngineDepthStencil();

	void Setting(D3D11_DEPTH_STENCIL_DESC _Desc) override;
	void IntoPipeline();
	ID3D11DepthStencilState* GetResource() const { return DepthStencil; }

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	D3D11_DEPTH_STENCIL_DESC Desc;
	ID3D11DepthStencilState* DepthStencil;
};