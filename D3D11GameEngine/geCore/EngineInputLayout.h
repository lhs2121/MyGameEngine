#pragma once
#include "DirectResource.h"

class EngineInputLayout : public DirectResource<EngineInputLayout>
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

	void SetResource(D3D11_INPUT_ELEMENT_DESC* Layouts, UINT LayoutNum, void* ShaderBytecode, SIZE_T BytecodeLength);
	void IntoPipeLine() override;

private:
	ID3D11InputLayout* LayoutPtr;
};