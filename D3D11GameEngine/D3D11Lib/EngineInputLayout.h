#pragma once
#include "D3D11API.h"

class EngineInputLayout : public IEngineInputLayout
{
public:
	EngineInputLayout();
	~EngineInputLayout();

	void Setting(D3D11_INPUT_ELEMENT_DESC* _Desc, UINT _ElementNum, IEngineVertexShader* _VSPtr) override;
	void IntoPipeline() override;

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	D3D11_INPUT_ELEMENT_DESC* Desc;
	ID3D11InputLayout* LayoutPtr;
};