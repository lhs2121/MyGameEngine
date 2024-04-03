#pragma once
#include <d3d11.h>
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"

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

	void Start();
	void Render();
	
	EngineVertexBuffer* VB = nullptr;
	EngineIndexBuffer* IB = nullptr;
	EngineInputLayout* IA = nullptr;

	EngineVertexShader* VS = nullptr;
	EnginePixelShader* PS = nullptr;

	float4 a = { 2,3 };
	float4x4 mat;
};	


