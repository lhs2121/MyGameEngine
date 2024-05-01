#pragma once
#include <d3d11.h>
#include "EngineTransform.h"
#include "EngineComponent.h"

class EngineRenderer : public EngineComponent
{
public:
	// constrcuter destructer
	EngineRenderer();
	~EngineRenderer();

	// delete Function
	EngineRenderer(const EngineRenderer& _Other) = delete;
	EngineRenderer(EngineRenderer&& _Other) noexcept = delete;
	EngineRenderer& operator=(const EngineRenderer& _Other) = delete;
	EngineRenderer& operator=(EngineRenderer&& _Other) noexcept = delete;

	void Start() override;
	void Render();
	void UpdateConstantBuffer();

	IEngineVertexBuffer* VB = nullptr;
	IEngineIndexBuffer* IB = nullptr;
	IEngineInputLayout* IA = nullptr;
	IEngineVertexShader* VS = nullptr;
	IEngineRasterizer* RS = nullptr;
	IEnginePixelShader* PS = nullptr;
	IEngineDepthStencil* DS = nullptr;

	UINT IndexCount;
	ID3D11Buffer* ConstantBuffer;
};	


