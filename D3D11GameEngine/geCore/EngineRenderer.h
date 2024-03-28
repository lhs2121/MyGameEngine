#pragma once
#include <d3d11.h>
#include "EngineVertexBuffer.h"

class EngineRenderer
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

	void Render();
	//void SetIndexBuffer();
	//void SetInputLayOut();
	//void SetSampler();
	//void SetRasterizer();
	//void SetVertexShader();
	//void SetPixelShader();
	//void SetConstantBuffer();
};

