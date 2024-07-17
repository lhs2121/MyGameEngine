#pragma once
#include "EngineComponent.h"
#include <D3D11Lib\D3D11Lib\D3D11API.h>

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
	void Update(float _Delta) override;

	virtual void Render();

	void SetTexture(EngineString _Name);
	void SetSampler(EngineString _Name);

protected:
	IEngineVertexBuffer* VB         = nullptr;
	IEngineIndexBuffer*  IB         = nullptr;
	IEngineInputLayout*  IA         = nullptr;
	IEngineVertexShader* VS         = nullptr;
	IEngineRasterizer*   RS         = nullptr;
	IEnginePixelShader*  PS         = nullptr;
	IEngineDepthStencil* DS         = nullptr;
	IEngineTexture*      CurTexture = nullptr;

	IEngineConstantBuffer* TransformBuffer = nullptr;
};	


