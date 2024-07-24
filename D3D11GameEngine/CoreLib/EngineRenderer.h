#pragma once
#include "EngineComponent.h"
#include <D3D11Lib\D3D11API.h>

class CoreAPI EngineRenderer : public EngineComponent
{
public:
	~EngineRenderer();

	void Awake() override;
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


