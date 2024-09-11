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
	if (ResourceContainer<Texture>::Resources.find(_name) == ResourceContainer<Texture>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<Texture>::Resources[_name];
}

VertexBuffer* Resource::FindVertexBuffer(const char* _name)
{
	if (ResourceContainer<VertexBuffer>::Resources.find(_name) == ResourceContainer<VertexBuffer>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<VertexBuffer>::Resources[_name];
}

IndexBuffer* Resource::FindIndexBuffer(const char* _name)
{
	if (ResourceContainer<IndexBuffer>::Resources.find(_name) == ResourceContainer<IndexBuffer>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<IndexBuffer>::Resources[_name];
}

InputLayout* Resource::FindInputLayout(const char* _name)
{
	if (ResourceContainer<InputLayout>::Resources.find(_name) == ResourceContainer<InputLayout>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<InputLayout>::Resources[_name];
}

VertexShader* Resource::FindVertexShader(const char* _name)
{
	if (ResourceContainer<VertexShader>::Resources.find(_name) == ResourceContainer<VertexShader>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<VertexShader>::Resources[_name];
}

PixelShader* Resource::FindPixelShader(const char* _name)
{
	if (ResourceContainer<PixelShader>::Resources.find(_name) == ResourceContainer<PixelShader>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<PixelShader>::Resources[_name];
}

Rasterizer* Resource::FindRasterizer(const char* _name)
{
	if (ResourceContainer<Rasterizer>::Resources.find(_name) == ResourceContainer<Rasterizer>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<Rasterizer>::Resources[_name];
}

DepthStencil* Resource::FindDepthStencil(const char* _name)
{
	if (ResourceContainer<DepthStencil>::Resources.find(_name) == ResourceContainer<DepthStencil>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<DepthStencil>::Resources[_name];
}

Sampler* Resource::FindSampler(const char* _name)
{
	if (ResourceContainer<Sampler>::Resources.find(_name) == ResourceContainer<Sampler>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<Sampler>::Resources[_name];
}

ConstantBuffer* Resource::FindConstantBuffer(const char* _name)
{
	if (ResourceContainer<ConstantBuffer>::Resources.find(_name) == ResourceContainer<ConstantBuffer>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<ConstantBuffer>::Resources[_name];
}

Mesh* Resource::FindMesh(const char* _name)
{
	if (ResourceContainer< Mesh>::Resources.find(_name) == ResourceContainer<Mesh>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<Mesh>::Resources[_name];
}

Material* Resource::FindMaterial(const char* _name)
{
	if (ResourceContainer<Material>::Resources.find(_name) == ResourceContainer<Material>::Resources.end())
	{
		return nullptr;
	};
	return ResourceContainer<Material>::Resources[_name];
}

void Resource::DeleteAllResource()
{
	for (auto& pair : ResourceContainer<VertexBuffer>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<VertexBuffer>::Resources.clear();

	for (auto& pair : ResourceContainer<IndexBuffer>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<IndexBuffer>::Resources.clear();

	for (auto& pair : ResourceContainer<InputLayout>::Resources)
	{
		InputLayout* pia = pair.second;
		delete pia;
	}
	ResourceContainer<InputLayout>::Resources.clear();

	for (auto& pair : ResourceContainer<VertexShader>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<VertexShader>::Resources.clear();

	for (auto& pair : ResourceContainer<PixelShader>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<PixelShader>::Resources.clear();

	for (auto& pair : ResourceContainer<Rasterizer>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<Rasterizer>::Resources.clear();

	for (auto& pair : ResourceContainer<DepthStencil>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<DepthStencil>::Resources.clear();

	for (auto& pair : ResourceContainer<Sampler>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<Sampler>::Resources.clear();

	for (auto& pair : ResourceContainer<Texture>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<Texture>::Resources.clear();

	for (auto& pair : ResourceContainer<ConstantBuffer>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<ConstantBuffer>::Resources.clear();

	for (auto& pair : ResourceContainer<Mesh>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<Mesh>::Resources.clear();

	for (auto& pair : ResourceContainer<Material>::Resources)
	{
		delete pair.second;
	}
	ResourceContainer<Material>::Resources.clear();
}

