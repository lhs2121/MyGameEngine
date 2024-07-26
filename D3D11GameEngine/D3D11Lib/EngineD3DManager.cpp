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
#include "EngineConstantBuffer.h"

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
	EngineSampler* ChildPtr = (EngineSampler*)NewSampler;
	ChildPtr->DevicePtr = Device;
	SamMap.insert(std::make_pair(_Name, NewSampler));
	return NewSampler;
}

IEngineConstantBuffer* EngineD3DManager::CreateConstantBuffer(EngineString _Name)
{
	IEngineConstantBuffer* NewCB = new EngineConstantBuffer();
	EngineConstantBuffer* ChildPtr = (EngineConstantBuffer*)NewCB;
	ChildPtr->DevicePtr = Device;
	CBMap.Add(_Name, NewCB);
	return NewCB;
}

IEngineVertexBuffer* EngineD3DManager::FindVertexBuffer(EngineString _Name)
{
	return (IEngineVertexBuffer*)VBMap.Get(_Name.c_str());
}

IEngineIndexBuffer* EngineD3DManager::FindIndexBuffer(EngineString _Name)
{
	return (IEngineIndexBuffer*)IBMap.Get(_Name.c_str());
}

IEngineInputLayout* EngineD3DManager::FindInputLayout(EngineString _Name)
{
	return (IEngineInputLayout*)IAMap.Get(_Name.c_str());
}

IEngineVertexShader* EngineD3DManager::FindVertexShader(EngineString _Name)
{
	return (IEngineVertexShader*)VSMap.Get(_Name.c_str());
}

IEngineRasterizer* EngineD3DManager::FindRasterizer(EngineString _Name)
{
	return (IEngineRasterizer*)RSMap.Get(_Name.c_str());
}

IEnginePixelShader* EngineD3DManager::FindPixelShader(EngineString _Name)
{
	return (IEnginePixelShader*)PSMap.Get(_Name.c_str());
}

IEngineDepthStencil* EngineD3DManager::FindDepthStencil(EngineString _Name)
{
	return (IEngineDepthStencil*)DSMap.Get(_Name.c_str());
}

IEngineTexture* EngineD3DManager::FindTexture(EngineString _Name)
{
	return (IEngineTexture*)TexMap.Get(_Name.c_str());
}

IEngineSampler* EngineD3DManager::FindSampler(EngineString _Name)
{
	return (IEngineSampler*)SamMap.Get(_Name.c_str());
}

IEngineConstantBuffer* EngineD3DManager::FindConstantBuffer(EngineString _Name)
{
	return (IEngineConstantBuffer*)CBMap.Get(_Name.c_str());
}

void EngineD3DManager::Release()
{
	
}
