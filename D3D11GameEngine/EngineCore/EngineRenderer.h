#pragma once
#include <d3d11.h>
#include "EngineTransform.h"
#include "EngineComponent.h"
#include "EngineConstantBuffer.h"

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
	virtual void Render();

	void SetTexture(EngineString _Name);
	void SetSampler(EngineString _Name);

	void UpdateConstantBuffer();

	IEngineVertexBuffer* VB = nullptr;
	IEngineIndexBuffer* IB = nullptr;
	IEngineInputLayout* IA = nullptr;
	IEngineVertexShader* VS = nullptr;
	IEngineRasterizer* RS = nullptr;
	IEnginePixelShader* PS = nullptr;
	IEngineDepthStencil* DS = nullptr;

	UINT IndexCount;
	SpriteData Data;
	ID3D11Buffer* ConstantBuffer;
	ID3D11Buffer* SpriteCBuffer;
};	


