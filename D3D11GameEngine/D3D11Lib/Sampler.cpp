#include "Pre.h"
#include "Sampler.h"

Sampler::Sampler()
{
}

Sampler::~Sampler()
{
	if (StatePtr != nullptr)
	{
		StatePtr->Release();
	}
}

ID3D11SamplerState* Sampler::GetState()
{
	return StatePtr;
}

void Sampler::Setting(ID3D11Device* DevicePtr, D3D11_SAMPLER_DESC* DescPtr)
{
	DevicePtr->CreateSamplerState(DescPtr, &StatePtr);
}

void Sampler::IntoPipeline(ID3D11DeviceContext* ContextPtr, ShaderType _Type, int SlotNum)
{
	switch (_Type)
	{
	case ShaderType::VS:
		ContextPtr->VSSetSamplers(SlotNum, 1, &StatePtr);
		break;
	case ShaderType::PS:
		ContextPtr->PSSetSamplers(SlotNum, 1, &StatePtr);
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
