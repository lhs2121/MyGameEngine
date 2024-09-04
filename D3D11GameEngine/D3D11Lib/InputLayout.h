#pragma once
#include "D3D11API.h"

class InputLayout : public IInputLayout
{
public:
	InputLayout();
	~InputLayout();

	void Setting(ID3D11Device* DevicePtr, IVertexBuffer* _pVB, IVertexShader* _pVS) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr) override;

private:
	D3D11_INPUT_ELEMENT_DESC* Desc;
	UINT ArrayCount = 0;
	ID3D11InputLayout* LayoutPtr;
};