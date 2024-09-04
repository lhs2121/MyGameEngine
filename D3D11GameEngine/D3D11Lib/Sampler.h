#pragma once
#include "D3D11API.h"

class Sampler : public ISampler
{
public:
	Sampler();
	~Sampler();
	
	void Setting(ID3D11Device* DevicePtr, D3D11_SAMPLER_DESC* DescPtr) override;
	void IntoPipeline(ID3D11DeviceContext* ContextPtr, ShaderType _Type, int SlotNum = 0) override;
    ID3D11SamplerState* GetState() override;

private:
	ID3D11SamplerState* StatePtr;
};