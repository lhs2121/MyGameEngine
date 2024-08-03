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

	void SetTexture(const char* _Name);
	void SetSampler(const char* _Name);

protected:
	IMesh* Mesh = nullptr;
	IMaterial* Material = nullptr;
	IEngineInputLayout* pIA = nullptr;
	IEngineConstantBuffer* TransformBuffer = nullptr;
};	


