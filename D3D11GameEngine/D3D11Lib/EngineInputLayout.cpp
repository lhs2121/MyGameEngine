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

	if (Desc != nullptr) 
	{
		delete[] Desc;
		Desc = nullptr;
	}
}

void EngineInputLayout::Setting(IEngineVertexBuffer* _pVB, IEngineVertexShader* _pVS)
{
	EngineVertexShader* pVS = (EngineVertexShader*)_pVS;
	EngineVertexBuffer* pVB = (EngineVertexBuffer*)_pVB;
	UINT VBSlotNum = pVB->GetSlotNumber();
	std::vector<EngineString> Sementics = pVS->GetSementics();
	int Size = Sementics.size();
	Desc = new D3D11_INPUT_ELEMENT_DESC[Size];
	
	UINT ByteOffset = 0;
	UINT FormatByte = 0;
	for (size_t i = 0; i < Size; i++)
	{
		EngineString Sementic = Sementics[i].c_str();
		DXGI_FORMAT Format;
		if (Sementic == "POSITION")
		{
			Desc[i].SemanticName = "POSITION";
			Desc[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			FormatByte = 16;
		}
		else if (Sementic == "TEXCOORD")
		{
			Desc[i].SemanticName = "TEXCOORD";
			Desc[i].Format = DXGI_FORMAT_R32G32_FLOAT;
			FormatByte = 8;
		}
		else if (Sementic == "COLOR")
		{
			Desc[i].SemanticName = "COLOR";
			Desc[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			FormatByte = 16;
		}

		Desc[i].SemanticIndex = 0;
		Desc[i].InputSlot = VBSlotNum;
		Desc[i].AlignedByteOffset = ByteOffset;
		Desc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		Desc[i].InstanceDataStepRate = 0;

		ByteOffset += FormatByte;
	}

	HRESULT Result = DevicePtr->CreateInputLayout(Desc, Size, pVS->GetShaderByteCode(), pVS->GetShaderByteLength(), &LayoutPtr);
}

void EngineInputLayout::IntoPipeline()
{
	ContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ContextPtr->IASetInputLayout(LayoutPtr);
}

