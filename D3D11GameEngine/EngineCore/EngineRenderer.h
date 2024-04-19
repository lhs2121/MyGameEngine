#pragma once
#include <d3d11.h>
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
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
	EngineVertexBuffer* VB = nullptr;
	EngineIndexBuffer* IB = nullptr;
	EngineInputLayout* IA = nullptr;
	EngineVertexShader* VS = nullptr;
	EnginePixelShader* PS = nullptr;
	
	ID3D11Buffer* constantBuffer;
};	


