#pragma once
#include "D3D11API.h"

class EngineInputLayout : public IEngineInputLayout
{
public:
	EngineInputLayout();
	~EngineInputLayout();

	void SetDesc(ShaderInput* _ShaderInputArray, UINT _ArrayCount) override;
	void Setting(IEngineVertexBuffer* _pVB, IEngineVertexShader* _pVS) override;
	void IntoPipeline() override;

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	D3D11_INPUT_ELEMENT_DESC* Desc;
	UINT ArrayCount = 0;
	ID3D11InputLayout* LayoutPtr;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
};