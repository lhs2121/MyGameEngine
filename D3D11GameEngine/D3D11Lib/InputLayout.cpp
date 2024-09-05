#include "Pre.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "VertexBuffer.h"

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
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

void InputLayout::Setting( IVertexBuffer* _pVB, IVertexShader* _pVS)
{
	VertexShader* pVS = (VertexShader*)_pVS;
	VertexBuffer* pVB = (VertexBuffer*)_pVB;
	UINT VBSlotNum = pVB->GetSlotNumber();
	std::vector<EngineString> Sementics = pVS->GetSementics();
	UINT Size = (UINT)Sementics.size();
	Desc = new D3D11_INPUT_ELEMENT_DESC[Size];
	
	UINT ByteOffset = 0;
	UINT FormatByte = 0;
	for (size_t i = 0; i < Size; i++)
	{
		EngineString Sementic = Sementics[i].c_str();
		DXGI_FORMAT Format = DXGI_FORMAT_UNKNOWN;
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

void InputLayout::IntoPipeline()
{
	ContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ContextPtr->IASetInputLayout(LayoutPtr);
}

