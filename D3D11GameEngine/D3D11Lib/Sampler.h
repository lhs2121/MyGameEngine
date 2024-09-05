#pragma once
#include "D3D11API.h"

class Sampler : public ISampler
{
public:
	Sampler();
	~Sampler();
	
	void Setting(D3D11_SAMPLER_DESC* DescPtr) override;
	void IntoPipeline(ShaderType _Type, int SlotNum = 0) override;
    ID3D11SamplerState* GetState() override;

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
private:
	ID3D11SamplerState* StatePtr;
};