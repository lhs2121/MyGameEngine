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

void EngineSampler::IntoPipeLine(ShaderType _Type, int SlotNum)
{
	switch (_Type)
	{
	case ShaderType::VS:
		DevicePtr->GetContext()->VSSetSamplers(SlotNum, 1, &StatePtr);
		break;
	case ShaderType::PS:
		DevicePtr->GetContext()->PSSetSamplers(SlotNum, 1, &StatePtr);
		break;
	case ShaderType::CS:
		break;
	case ShaderType::HS:
		break;
	case ShaderType::DS:
		break;
	case ShaderType::GS:
		break;
	default:
		break;
	}
	
}
