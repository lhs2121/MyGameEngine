#pragma once
#include "EngineD3DResource.h"

class EngineInputLayout : public EngineD3DResource<EngineInputLayout>
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

	D3D11_INPUT_ELEMENT_DESC* GetLayoutDesc();
	void SetResource(D3D11_INPUT_ELEMENT_DESC* Layouts, UINT LayoutNum, void* ShaderBytecode, SIZE_T BytecodeLength);
	void IntoPipeLine() override;
	void Release() override;
private:
	D3D11_INPUT_ELEMENT_DESC* DescPtr;
	ID3D11InputLayout* LayoutPtr;
};