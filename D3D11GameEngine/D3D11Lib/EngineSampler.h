#pragma once
#include "D3D11API.h"

class EngineSampler : public IEngineSampler
{
public:
	EngineSampler();
	~EngineSampler();
	
	void Setting(D3D11_SAMPLER_DESC* DescPtr) override;
	void IntoPipeline(ShaderType _Type, int SlotNum = 0) override;
    ID3D11SamplerState* GetState() override;

private:
	void SetDevice(ID3D11Device* _DevicePtr) override { DevicePtr = _DevicePtr; }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override { ContextPtr = _ContextPtr; }

	ID3D11Device* DevicePtr = nullptr;
	ID3D11DeviceContext* ContextPtr = nullptr;
	ID3D11SamplerState* StatePtr;
};