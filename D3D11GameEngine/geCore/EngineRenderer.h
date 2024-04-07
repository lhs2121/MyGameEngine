#pragma once
#include <d3d11.h>
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineTransform.h"
#include "EngineObject.h"

class EngineRenderer : public EngineObject
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
	
	EngineVertexBuffer* VB = nullptr;
	EngineIndexBuffer* IB = nullptr;
	EngineInputLayout* IA = nullptr;
	EngineVertexShader* VS = nullptr;
	EnginePixelShader* PS = nullptr;

	EngineTransform* Transform = nullptr;
};	


