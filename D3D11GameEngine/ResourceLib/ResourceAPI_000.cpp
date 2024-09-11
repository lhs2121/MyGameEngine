#include "Pre.h"
#include "ResourceAPI.h"
#include "ResourceContainer.h"
#include "Device.h"

void CreateDevice(IDevice** ppIDevice)
{
	*ppIDevice = new Device();
}

void DeleteDevice(IDevice* pIDevice)
{
	Device* pCast = (Device*)pIDevice;
	delete pCast;
}

Texture* Resource::FindTexture(const char* _name)
{
	return ResourceContainer<Texture>::Find(_name);
}

VertexBuffer* Resource::FindVertexBuffer(const char* _name)
{
	return ResourceContainer<VertexBuffer>::Find(_name);
}

IndexBuffer* Resource::FindIndexBuffer(const char* _name)
{
	return ResourceContainer<IndexBuffer>::Find(_name);
}

VertexShader* Resource::FindVertexShader(const char* _name)
{
	return ResourceContainer<VertexShader>::Find(_name);
}

PixelShader* Resource::FindPixelShader(const char* _name)
{
	return ResourceContainer<PixelShader>::Find(_name);
}

Rasterizer* Resource::FindRasterizer(const char* _name)
{
	return ResourceContainer<Rasterizer>::Find(_name);
}

DepthStencil* Resource::FindDepthStencil(const char* _name)
{
	return ResourceContainer<DepthStencil>::Find(_name);
}

Sampler* Resource::FindSampler(const char* _name)
{
	return ResourceContainer<Sampler>::Find(_name);
}

ConstantBuffer* Resource::FindConstantBuffer(const char* _name)
{
	return ResourceContainer<ConstantBuffer>::Find(_name);
}

Mesh* Resource::FindMesh(const char* _name)
{
	return ResourceContainer<Mesh>::Find(_name);
}

Material* Resource::FindMaterial(const char* _name)
{
	return ResourceContainer<Material>::Find(_name);
}

