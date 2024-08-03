#include "Pre.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EngineVertexBuffer.h"

EngineInputLayout::EngineInputLayout()
{
}

EngineInputLayout::~EngineInputLayout()
{
	if (LayoutPtr != nullptr)
	{
		LayoutPtr->Release();
		LayoutPtr = nullptr;
	}
}

void EngineInputLayout::SetDesc(ShaderInput* _ShaderInputArray, UINT _ArrayCount)
{
	Desc = new D3D11_INPUT_ELEMENT_DESC[_ArrayCount];
	ArrayCount = _ArrayCount;
	UINT CurOffset = 0;

	for (size_t i = 0; i < _ArrayCount; i++)
	{
		ShaderInput Element = _ShaderInputArray[i];
		switch (Element)
		{
		case ShaderInput::POSITION:
			Desc[i] = { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, CurOffset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			CurOffset += 16;
			break;
		case ShaderInput::TEXCOORD:
			Desc[i] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, CurOffset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			CurOffset += 4;
			break;
		case ShaderInput::COLOR:
			Desc[i] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, CurOffset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			CurOffset += 16;
			break;
		default:
			break;
		}
	}
}

void EngineInputLayout::Setting(IEngineVertexBuffer* _pVB, IEngineVertexShader* _pVS)
{
	EngineVertexShader* pVS = (EngineVertexShader*)_pVS;
	EngineVertexBuffer* pVB = (EngineVertexBuffer*)_pVB;
	for (size_t i = 0; i < ArrayCount; i++)
	{
		Desc[i].InputSlot = pVB->GetSlotNumber();
	}
	HRESULT Result = DevicePtr->CreateInputLayout(Desc, ArrayCount, pVS->GetShaderByteCode(), pVS->GetShaderByteLength(), &LayoutPtr);
}

void EngineInputLayout::IntoPipeline()
{
	ContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ContextPtr->IASetInputLayout(LayoutPtr);
}

