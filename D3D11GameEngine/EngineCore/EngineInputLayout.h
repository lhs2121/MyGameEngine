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

	void CreateResource(void* ShaderBytecode, SIZE_T BytecodeLength);
	void SetDesc(D3D11_INPUT_ELEMENT_DESC _Desc);
	void IntoPipeLine() override;
private:
	D3D11_INPUT_ELEMENT_DESC LayoutDesc;
	ID3D11InputLayout* LayoutPtr;
};