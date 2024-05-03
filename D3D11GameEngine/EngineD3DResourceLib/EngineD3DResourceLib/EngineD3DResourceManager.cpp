#include "Pre.h"
#include "EngineD3DResourceManager.h"
#include "EngineDevice.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineRasterizer.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineDepthStencil.h"
#include "EngineVertexFormat.h"
#include <fstream>
#include <iostream>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "EngineBase.lib")

IEngineDevice* EngineD3DResourceManager::CreateDevice()
{
	IEngineDevice* NewDevice = new EngineDevice();
	EngineDevice* ChildPtr = (EngineDevice*)NewDevice;
	m_pDevice = NewDevice;
	ChildPtr->SetManager(this);
	return NewDevice;
}

IEngineVertexBuffer* EngineD3DResourceManager::CreateVertexBuffer(const char* _Name)
{
	IEngineVertexBuffer* NewVertexBuffer = new EngineVertexBuffer();
	EngineVertexBuffer* ChildPtr = (EngineVertexBuffer*)NewVertexBuffer;
	ChildPtr->SetDevicePtr(m_pDevice);
	VBMap.insert(std::make_pair(_Name, NewVertexBuffer));
	return NewVertexBuffer;
}

IEngineIndexBuffer* EngineD3DResourceManager::CreateIndexBuffer(const char* _Name)
{
	IEngineIndexBuffer* NewIndexBuffer = new EngineIndexBuffer();
	EngineIndexBuffer* ChildPtr = (EngineIndexBuffer*)NewIndexBuffer;
	ChildPtr->SetDevicePtr(m_pDevice);
	IBMap.insert(std::make_pair(_Name, NewIndexBuffer));
	return NewIndexBuffer;
}

IEngineInputLayout* EngineD3DResourceManager::CreateInputLayout(const char* _Name)
{
	IEngineInputLayout* NewInputLayout = new EngineInputLayout();
	EngineInputLayout* ChildPtr = (EngineInputLayout*)NewInputLayout;
	ChildPtr->SetDevicePtr(m_pDevice);
	IAMap.insert(std::make_pair(_Name, NewInputLayout));
	return NewInputLayout;
}

IEngineVertexShader* EngineD3DResourceManager::CreateVertexShader(const char* _Name)
{
	IEngineVertexShader* NewVertexShader = new EngineVertexShader();
	EngineVertexShader* ChildPtr = (EngineVertexShader*)NewVertexShader;
	ChildPtr->SetDevicePtr(m_pDevice);
	VSMap.insert(std::make_pair(_Name, NewVertexShader));
	return NewVertexShader;
}

IEnginePixelShader* EngineD3DResourceManager::CreatePixelShader(const char* _Name)
{
	IEnginePixelShader* NewPixelShader = new EnginePixelShader();
	EnginePixelShader* ChildPtr = (EnginePixelShader*)NewPixelShader;
	ChildPtr->SetDevicePtr(m_pDevice);
	PSMap.insert(std::make_pair(_Name, NewPixelShader));
	return NewPixelShader;
}

IEngineRasterizer* EngineD3DResourceManager::CreateRasterizer(const char* _Name)
{
	IEngineRasterizer* NewRasterizer = new EngineRasterizer();
	EngineRasterizer* ChildPtr = (EngineRasterizer*)NewRasterizer;
	ChildPtr->SetDevicePtr(m_pDevice);
	RSMap.insert(std::make_pair(_Name, NewRasterizer));
	return NewRasterizer;
}

IEngineDepthStencil* EngineD3DResourceManager::CreateDepthStencil(const char* _Name)
{
	IEngineDepthStencil* NewDepthStencil = new EngineDepthStencil();
	EngineDepthStencil* ChildPtr = (EngineDepthStencil*)NewDepthStencil;
	ChildPtr->SetDevicePtr(m_pDevice);
	DSMap.insert(std::make_pair(_Name, NewDepthStencil));
	return NewDepthStencil;
}

void EngineD3DResourceManager::SettingVertexBuffer(IEngineVertexBuffer* pBuffer, VERTEX_POS_COLOR* pVertices, int VertexSize)
{
	EngineVertexBuffer* ChildPtr = (EngineVertexBuffer*)pBuffer;

	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;

	Data.pSysMem = pVertices;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = VertexSize;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	ChildPtr->Strides = sizeof(VERTEX_POS_COLOR);
	ChildPtr->Offsets = 0;
	HRESULT Result = m_pDevice->GetDevice()->CreateBuffer(&Desc, &Data, &ChildPtr->BufferPtr);
}

void EngineD3DResourceManager::SettingIndexBuffer(IEngineIndexBuffer* pBuffer, UINT* Indices, int IndexSize)
{
	EngineIndexBuffer* ChildPtr = (EngineIndexBuffer*)pBuffer;

	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = Indices;
	Data.SysMemPitch = 0;
	Data.SysMemSlicePitch = 0;

	Desc.ByteWidth = IndexSize;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Desc.CPUAccessFlags = 0;
	Desc.StructureByteStride = 0;
	Desc.MiscFlags = 0;

	ChildPtr->Strides = sizeof(UINT);
	ChildPtr->Offsets = 0;

	ChildPtr->IndexCount = IndexSize / sizeof(UINT);
	HRESULT Result = m_pDevice->GetDevice()->CreateBuffer(&Desc, &Data, &ChildPtr->BufferPtr);
}

void EngineD3DResourceManager::SettingInputLayout(IEngineInputLayout* pLayout, UINT _ElementNum,
	D3D11_INPUT_ELEMENT_DESC* _Desc, void* ShaderBytecode, SIZE_T BytecodeLength)
{
	EngineInputLayout* ChildPtr = (EngineInputLayout*)pLayout;
	ChildPtr->ElementNum = _ElementNum;
	ChildPtr->LayoutDesc = _Desc;
	HRESULT Result = m_pDevice->GetDevice()->CreateInputLayout(ChildPtr->LayoutDesc, ChildPtr->ElementNum, ShaderBytecode, BytecodeLength, &ChildPtr->LayoutPtr);
}

void EngineD3DResourceManager::SettingVertexShader(IEngineVertexShader* pShader, const char* _Name, const char* _Path)
{
	EngineVertexShader* ChildPtr = (EngineVertexShader*)pShader;

	std::string MainFuncName = _Name;
	MainFuncName += "_VS";

	std::string PathString = _Path;
	std::wstring WPathString = EngineString::GetWideString(PathString);

	int Flag;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;

#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* ErrorBlob = nullptr;



	HRESULT Result = D3DCompileFromFile(WPathString.c_str(),
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "vs_5_0", Flag, 0, &ChildPtr->ShaderBlob, &ErrorBlob);

	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}

	HRESULT R = m_pDevice->GetDevice()->CreateVertexShader(ChildPtr->ShaderBlob->GetBufferPointer(), ChildPtr->ShaderBlob->GetBufferSize(), nullptr, &ChildPtr->ShaderPtr);
}

void EngineD3DResourceManager::SettingPixelShader(IEnginePixelShader* pShader, const char* _Name, const char* _Path)
{
	EnginePixelShader* ChildPtr = (EnginePixelShader*)pShader;

	std::string MainFuncName = _Name;
	MainFuncName += "_PS";

	std::string PathString = _Path;
	std::wstring WPathString = EngineString::GetWideString(PathString);

	int Flag;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;

#endif
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;


	ID3DBlob* ErrorBlob = nullptr;

	HRESULT Result = D3DCompileFromFile(WPathString.c_str(),
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, MainFuncName.c_str(), "ps_5_0", Flag, 0, &ChildPtr->ShaderBlob, &ErrorBlob);


	if (FAILED(Result))
	{
		if (ErrorBlob)
		{
			OutputDebugStringA(static_cast<const char*>(ErrorBlob->GetBufferPointer()));
			ErrorBlob->Release();
		}
	}

	m_pDevice->GetDevice()->CreatePixelShader(ChildPtr->ShaderBlob->GetBufferPointer(), ChildPtr->ShaderBlob->GetBufferSize(), nullptr, &ChildPtr->ShaderPtr);
}

void EngineD3DResourceManager::SettingRasterizer(IEngineRasterizer* pRasterizer, D3D11_RASTERIZER_DESC _Desc)
{
	EngineRasterizer* ChildPtr = (EngineRasterizer*)pRasterizer;

	ChildPtr->Desc = _Desc;
	m_pDevice->GetDevice()->CreateRasterizerState(&ChildPtr->Desc, &ChildPtr->RasterizePtr);
}

void EngineD3DResourceManager::SettingDepthStencil(IEngineDepthStencil* pDepthStencil, D3D11_DEPTH_STENCIL_DESC _Desc)
{
	EngineDepthStencil* ChildPtr = (EngineDepthStencil*)pDepthStencil;

	ChildPtr->m_Desc = _Desc;
	m_pDevice->GetDevice()->CreateDepthStencilState(&ChildPtr->m_Desc, &ChildPtr->m_pDepthStencil);
}

IEngineVertexBuffer* EngineD3DResourceManager::FindVertexBuffer(const char* _Name)
{
	if (VBMap.find(_Name) != VBMap.end())
	{
		return VBMap[_Name];
	}
	return nullptr;;
}

IEngineIndexBuffer* EngineD3DResourceManager::FindIndexBuffer(const char* _Name)
{
	if (IBMap.find(_Name) != IBMap.end())
	{
		return IBMap[_Name];
	}
	return nullptr;
}

IEngineInputLayout* EngineD3DResourceManager::FindInputLayout(const char* _Name)
{
	if (IAMap.find(_Name) != IAMap.end())
	{
		return IAMap[_Name];
	}
	return nullptr;
}

IEngineVertexShader* EngineD3DResourceManager::FindVertexShader(const char* _Name)
{
	if (VSMap.find(_Name) != VSMap.end())
	{
		return VSMap[_Name];
	}
	return nullptr;
}

IEngineRasterizer* EngineD3DResourceManager::FindRasterizer(const char* _Name)
{
	if (RSMap.find(_Name) != RSMap.end())
	{
		return RSMap[_Name];
	}
	return nullptr;
}

IEnginePixelShader* EngineD3DResourceManager::FindPixelShader(const char* _Name)
{
	if (PSMap.find(_Name) != PSMap.end())
	{
		return PSMap[_Name];
	}
	return nullptr;
}

IEngineDepthStencil* EngineD3DResourceManager::FindDepthStencil(const char* _Name)
{
	if (DSMap.find(_Name) != DSMap.end())
	{
		return DSMap[_Name];
	}
	return nullptr;
}

void EngineD3DResourceManager::DeleteAllResource()
{
	for (std::pair<std::string, IEngineVertexBuffer*> pair : VBMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	VBMap.clear();

	for (std::pair<std::string, IEngineIndexBuffer*> pair : IBMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	IBMap.clear();

	for (std::pair<std::string, IEngineInputLayout*> pair : IAMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	IAMap.clear();

	for (std::pair<std::string, IEngineVertexShader*> pair : VSMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	VSMap.clear();

	for (std::pair<std::string, IEngineRasterizer*> pair : RSMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	RSMap.clear();

	for (std::pair<std::string, IEnginePixelShader*> pair : PSMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	PSMap.clear();

	for (std::pair<std::string, IEngineDepthStencil*> pair : DSMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	DSMap.clear();
}

