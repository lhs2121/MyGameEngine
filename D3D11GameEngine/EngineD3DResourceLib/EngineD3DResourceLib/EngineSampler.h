#pragma once
#include "EngineD3DInterface.h"

class EngineSampler : public IEngineSampler
{
	friend class EngineD3DManager;
public:
	// constrcuter destructer
	EngineSampler();
	~EngineSampler();

	// delete Function
	EngineSampler(const EngineSampler& _Other) = delete;
	EngineSampler(EngineSampler&& _Other) noexcept = delete;
	EngineSampler& operator=(const EngineSampler& _Other) = delete;
	EngineSampler& operator=(EngineSampler&& _Other) noexcept = delete;

    ID3D11SamplerState* GetState() override;
	void Setting(D3D11_SAMPLER_DESC* DescPtr) override;
	void Release() override;

private:
	ID3D11Device* DevicePtr;
	ID3D11SamplerState* StatePtr;
};