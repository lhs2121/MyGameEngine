#include "Pre.h"
#include "EngineD3DResourceManager.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "EngineInputLayout.h"
#include "EngineRasterizer.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineDepthStencil.h"
#include "EngineVertexFormat.h"
#include "EngineTexture.h"

IEngineDevice* EngineD3DResourceManager::CreateDevice()
{
	IEngineDevice* NewDevice = new EngineDevice();
	Device = (EngineDevice*)NewDevice;
	return NewDevice;
}

IEngineVertexBuffer* EngineD3DResourceManager::CreateVertexBuffer(const char* _Name)
{
	IEngineVertexBuffer* NewVertexBuffer = new EngineVertexBuffer();
	EngineVertexBuffer* ChildPtr = (EngineVertexBuffer*)NewVertexBuffer;
	ChildPtr->SetDevicePtr(Device);
	VBMap.insert(std::make_pair(_Name, NewVertexBuffer));
	return NewVertexBuffer;
}

IEngineIndexBuffer* EngineD3DResourceManager::CreateIndexBuffer(const char* _Name)
{
	IEngineIndexBuffer* NewIndexBuffer = new EngineIndexBuffer();
	EngineIndexBuffer* ChildPtr = (EngineIndexBuffer*)NewIndexBuffer;
	ChildPtr->SetDevicePtr(Device);
	IBMap.insert(std::make_pair(_Name, NewIndexBuffer));
	return NewIndexBuffer;
}

IEngineInputLayout* EngineD3DResourceManager::CreateInputLayout(const char* _Name)
{
	IEngineInputLayout* NewInputLayout = new EngineInputLayout();
	EngineInputLayout* ChildPtr = (EngineInputLayout*)NewInputLayout;
	ChildPtr->SetDevicePtr(Device);
	IAMap.insert(std::make_pair(_Name, NewInputLayout));
	return NewInputLayout;
}

IEngineVertexShader* EngineD3DResourceManager::CreateVertexShader(const char* _Name)
{
	IEngineVertexShader* NewVertexShader = new EngineVertexShader();
	EngineVertexShader* ChildPtr = (EngineVertexShader*)NewVertexShader;
	ChildPtr->SetDevicePtr(Device);
	VSMap.insert(std::make_pair(_Name, NewVertexShader));
	return NewVertexShader;
}

IEnginePixelShader* EngineD3DResourceManager::CreatePixelShader(const char* _Name)
{
	IEnginePixelShader* NewPixelShader = new EnginePixelShader();
	EnginePixelShader* ChildPtr = (EnginePixelShader*)NewPixelShader;
	ChildPtr->SetDevicePtr(Device);
	PSMap.insert(std::make_pair(_Name, NewPixelShader));
	return NewPixelShader;
}

IEngineRasterizer* EngineD3DResourceManager::CreateRasterizer(const char* _Name)
{
	IEngineRasterizer* NewRasterizer = new EngineRasterizer();
	EngineRasterizer* ChildPtr = (EngineRasterizer*)NewRasterizer;
	ChildPtr->SetDevicePtr(Device);
	RSMap.insert(std::make_pair(_Name, NewRasterizer));
	return NewRasterizer;
}

IEngineDepthStencil* EngineD3DResourceManager::CreateDepthStencil(const char* _Name)
{
	IEngineDepthStencil* NewDepthStencil = new EngineDepthStencil();
	EngineDepthStencil* ChildPtr = (EngineDepthStencil*)NewDepthStencil;
	ChildPtr->SetDevicePtr(Device);
	DSMap.insert(std::make_pair(_Name, NewDepthStencil));
	return NewDepthStencil;
}

IEngineTexture* EngineD3DResourceManager::CreateTexture(const char* _Name)
{
	IEngineTexture* NewTexture = new EngineTexture();
	EngineTexture* ChildPtr = (EngineTexture*)NewTexture;
	ChildPtr->SetDevicePtr(Device);
	TexMap.insert(std::make_pair(_Name, NewTexture));
	return NewTexture;
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

IEngineTexture* EngineD3DResourceManager::FindTexture(const char* _Name)
{
	if (TexMap.find(_Name) != TexMap.end())
	{
		return TexMap[_Name];
	}
	return nullptr;
}

void EngineD3DResourceManager::Release()
{
	for (std::pair<std::string, IEngineVertexBuffer*> pair : VBMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	VBMap.clear();

	for (std::pair<std::string, IEngineIndexBuffer*> pair : IBMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	IBMap.clear();

	for (std::pair<std::string, IEngineInputLayout*> pair : IAMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	IAMap.clear();

	for (std::pair<std::string, IEngineVertexShader*> pair : VSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	VSMap.clear();

	for (std::pair<std::string, IEngineRasterizer*> pair : RSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	RSMap.clear();

	for (std::pair<std::string, IEnginePixelShader*> pair : PSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	PSMap.clear();

	for (std::pair<std::string, IEngineDepthStencil*> pair : DSMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	DSMap.clear();

	for (std::pair<std::string, IEngineTexture*> pair : TexMap)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}
	TexMap.clear();
}
