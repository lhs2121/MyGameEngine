#include "Pre.h"
#include "EngineSampler.h"

EngineSampler::EngineSampler()
{
}

EngineSampler::~EngineSampler()
{
	StatePtr->Release();
}

ID3D11SamplerState* EngineSampler::GetState()
{
	return StatePtr;
}

void EngineSampler::Setting(D3D11_SAMPLER_DESC* DescPtr)
{
    DevicePtr->GetDevice()->CreateSamplerState(DescPtr, &StatePtr);
}

void EngineSampler::Release()
{
}

void EngineSampler::IntoPipeLine()
{
	DevicePtr->GetContext()->PSSetSamplers(0, 1, &StatePtr);
}
