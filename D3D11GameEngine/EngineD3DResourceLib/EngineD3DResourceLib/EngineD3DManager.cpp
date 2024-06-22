#include "Pre.h"
#include "EngineD3DManager.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineRasterizer.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineDepthStencil.h"
#include "EngineVertexFormat.h"
#include "EngineTexture.h"
#include "EngineSampler.h"

IEngineDevice* EngineD3DManager::CreateDevice()
{
	IEngineDevice* NewDevice = new EngineDevice();
	Device = (EngineDevice*)NewDevice;
	return NewDevice;
}

IEngineVertexBuffer* EngineD3DManager::CreateVertexBuffer(EngineString _Name)
{
	IEngineVertexBuffer* NewVertexBuffer = new EngineVertexBuffer();
	EngineVertexBuffer* ChildPtr = (EngineVertexBuffer*)NewVertexBuffer;
	ChildPtr->SetDevicePtr(Device);
	VBMap.insert(std::make_pair(_Name, NewVertexBuffer));
	return NewVertexBuffer;
}

IEngineIndexBuffer* EngineD3DManager::CreateIndexBuffer(EngineString _Name)
{
	IEngineIndexBuffer* NewIndexBuffer = new EngineIndexBuffer();
	EngineIndexBuffer* ChildPtr = (EngineIndexBuffer*)NewIndexBuffer;
	ChildPtr->SetDevicePtr(Device);
	IBMap.insert(std::make_pair(_Name, NewIndexBuffer));
	return NewIndexBuffer;
}

IEngineInputLayout* EngineD3DManager::CreateInputLayout(EngineString _Name)
{
	IEngineInputLayout* NewInputLayout = new EngineInputLayout();
	EngineInputLayout* ChildPtr = (EngineInputLayout*)NewInputLayout;
	ChildPtr->SetDevicePtr(Device);
	IAMap.insert(std::make_pair(_Name, NewInputLayout));
	return NewInputLayout;
}

IEngineVertexShader* EngineD3DManager::CreateVertexShader(EngineString _Name)
{
	IEngineVertexShader* NewVertexShader = new EngineVertexShader();
	EngineVertexShader* ChildPtr = (EngineVertexShader*)NewVertexShader;
	ChildPtr->SetDevicePtr(Device);
	VSMap.insert(std::make_pair(_Name, NewVertexShader));
	return NewVertexShader;
}

IEnginePixelShader* EngineD3DManager::CreatePixelShader(EngineString _Name)
{
	IEnginePixelShader* NewPixelShader = new EnginePixelShader();
	EnginePixelShader* ChildPtr = (EnginePixelShader*)NewPixelShader;
	ChildPtr->SetDevicePtr(Device);
	PSMap.insert(std::make_pair(_Name, NewPixelShader));
	return NewPixelShader;
}

IEngineRasterizer* EngineD3DManager::CreateRasterizer(EngineString _Name)
{
	IEngineRasterizer* NewRasterizer = new EngineRasterizer();
	EngineRasterizer* ChildPtr = (EngineRasterizer*)NewRasterizer;
	ChildPtr->SetDevicePtr(Device);
	RSMap.insert(std::make_pair(_Name, NewRasterizer));
	return NewRasterizer;
}

IEngineDepthStencil* EngineD3DManager::CreateDepthStencil(EngineString _Name)
{
	IEngineDepthStencil* NewDepthStencil = new EngineDepthStencil();
	EngineDepthStencil* ChildPtr = (EngineDepthStencil*)NewDepthStencil;
	ChildPtr->SetDevicePtr(Device);
	DSMap.insert(std::make_pair(_Name, NewDepthStencil));
	return NewDepthStencil;
}

IEngineTexture* EngineD3DManager::CreateTexture(EngineString _Name)
{
	IEngineTexture* NewTexture = new EngineTexture();
	EngineTexture* ChildPtr = (EngineTexture*)NewTexture;
	ChildPtr->SetDevicePtr(Device);
	TexMap.insert(std::make_pair(_Name, NewTexture));
	return NewTexture;
}

IEngineSampler* EngineD3DManager::CreateSampler(EngineString _Name)
{
	IEngineSampler* NewSampler = new EngineSampler();
	NewSampler->
	TexMap.insert(std::make_pair(_Name, NewTexture));
	return NewTexture;
}

IEngineVertexBuffer* EngineD3DManager::FindVertexBuffer(const char* _Name)
{
	if (VBMap.find(_Name) != VBMap.end())
	{
		return VBMap[_Name];
	}
	return nullptr;;
}

IEngineIndexBuffer* EngineD3DManager::FindIndexBuffer(const char* _Name)
{
	if (IBMap.find(_Name) != IBMap.end())
	{
		return IBMap[_Name];
	}
	return nullptr;
}

IEngineInputLayout* EngineD3DManager::FindInputLayout(const char* _Name)
{
	if (IAMap.find(_Name) != IAMap.end())
	{
		return IAMap[_Name];
	}
	return nullptr;
}

IEngineVertexShader* EngineD3DManager::FindVertexShader(const char* _Name)
{
	if (VSMap.find(_Name) != VSMap.end())
	{
		return VSMap[_Name];
	}
	return nullptr;
}

IEngineRasterizer* EngineD3DManager::FindRasterizer(const char* _Name)
{
	if (RSMap.find(_Name) != RSMap.end())
	{
		return RSMap[_Name];
	}
	return nullptr;
}

IEnginePixelShader* EngineD3DManager::FindPixelShader(const char* _Name)
{
	if (PSMap.find(_Name) != PSMap.end())
	{
		return PSMap[_Name];
	}
	return nullptr;
}

IEngineDepthStencil* EngineD3DManager::FindDepthStencil(const char* _Name)
{
	if (DSMap.find(_Name) != DSMap.end())
	{
		return DSMap[_Name];
	}
	return nullptr;
}

IEngineTexture* EngineD3DManager::FindTexture(const char* _Name)
{
	if (TexMap.find(_Name) != TexMap.end())
	{
		return TexMap[_Name];
	}
	return nullptr;
}

IEngineSampler* EngineD3DManager::FindSampler(const char* _Name)
{
	if (SamMap.find(_Name) != SamMap.end())
	{
		return SamMap[_Name];
	}
	return nullptr;
}

void EngineD3DManager::Release()
{
	for (auto& pair : VBMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	VBMap.clear();

	for (auto& pair : IBMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	IBMap.clear();

	for (auto& pair : IAMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	IAMap.clear();

	for (auto& pair : VSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	VSMap.clear();

	for (auto& pair : RSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	RSMap.clear();

	for (auto& pair : PSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	PSMap.clear();

	for (auto& pair : DSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	DSMap.clear();

	for (auto& pair : TexMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	TexMap.clear();
}
