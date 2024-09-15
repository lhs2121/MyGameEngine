#include "Pre.h"
#include "ResourceAPI.h"
#include "ResMap.h"

Texture* Resource::FindTexture(const char* _name)
{
	return ResMap<Texture>::Find(_name);
}

VertexBuffer* Resource::FindVertexBuffer(const char* _name)
{
	return ResMap<VertexBuffer>::Find(_name);
}

IndexBuffer* Resource::FindIndexBuffer(const char* _name)
{
	return ResMap<IndexBuffer>::Find(_name);
}

InputLayout* Resource::FindInputLayout(const char* _name)
{
	return ResMap<InputLayout>::Find(_name);
}

VertexShader* Resource::FindVertexShader(const char* _name)
{
	return ResMap<VertexShader>::Find(_name);
}

PixelShader* Resource::FindPixelShader(const char* _name)
{
	return ResMap<PixelShader>::Find(_name);
}

Rasterizer* Resource::FindRasterizer(const char* _name)
{
	return ResMap<Rasterizer>::Find(_name);
}

DepthStencil* Resource::FindDepthStencil(const char* _name)
{
	return ResMap<DepthStencil>::Find(_name);
}

Sampler* Resource::FindSampler(const char* _name)
{
	return ResMap<Sampler>::Find(_name);
}

ConstantBuffer* Resource::FindConstantBuffer(const char* _name)
{
	return ResMap<ConstantBuffer>::Find(_name);
}

Blend* Resource::FindBlend(const char* _name)
{
	return ResMap<Blend>::Find(_name);
}

Mesh* Resource::FindMesh(const char* _name)
{
	return ResMap<Mesh>::Find(_name);
}

Material* Resource::FindMaterial(const char* _name)
{
	return ResMap<Material>::Find(_name);
}

void Resource::DeleteAllResource()
{
	for (auto& pair : ResMap<VertexBuffer>::map)
	{
		delete pair.second;
	}
	ResMap<VertexBuffer>::map.clear();

	for (auto& pair : ResMap<IndexBuffer>::map)
	{
		delete pair.second;
	}
	ResMap<IndexBuffer>::map.clear();

	for (auto& pair : ResMap<InputLayout>::map)
	{
		delete pair.second;
	}
	ResMap<InputLayout>::map.clear();

	for (auto& pair : ResMap<VertexShader>::map)
	{
		delete pair.second;
	}
	ResMap<VertexShader>::map.clear();

	for (auto& pair : ResMap<PixelShader>::map)
	{
		delete pair.second;
	}
	ResMap<PixelShader>::map.clear();

	for (auto& pair : ResMap<Rasterizer>::map)
	{
		delete pair.second;
	}
	ResMap<Rasterizer>::map.clear();

	for (auto& pair : ResMap<DepthStencil>::map)
	{
		delete pair.second;
	}
	ResMap<DepthStencil>::map.clear();

	for (auto& pair : ResMap<Sampler>::map)
	{
		delete pair.second;
	}
	ResMap<Sampler>::map.clear();

	for (auto& pair : ResMap<Texture>::map)
	{
		delete pair.second;
	}
	ResMap<Texture>::map.clear();

	for (auto& pair : ResMap<ConstantBuffer>::map)
	{
		delete pair.second;
	}
	ResMap<ConstantBuffer>::map.clear();

	for (auto& pair : ResMap<Blend>::map)
	{
		delete pair.second;
	}
	ResMap<Blend>::map.clear();

	for (auto& pair : ResMap<Mesh>::map)
	{
		delete pair.second;
	}
	ResMap<Mesh>::map.clear();

	for (auto& pair : ResMap<Material>::map)
	{
		delete pair.second;
	}
	ResMap<Material>::map.clear();
}


