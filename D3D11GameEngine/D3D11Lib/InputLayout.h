#pragma once
#include "D3D11API.h"

class InputLayout : public IInputLayout
{
public:
	InputLayout();
	~InputLayout();

	void Setting( IVertexBuffer* _pVB, IVertexShader* _pVS) override;
	void IntoPipeline() override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
private:
	D3D11_INPUT_ELEMENT_DESC* Desc;
	UINT ArrayCount = 0;
	ID3D11InputLayout* LayoutPtr;
};