#include "Pre.h"
#include "ResourceAPI.h"
#include "ResMap.h"
#include <direct.h>	//getcwd


Rasterizer* Resource::CreateRasterizer(const char* _name, D3D11_RASTERIZER_DESC _desc)
{
	Rasterizer* newRasterizer = new Rasterizer();
	newRasterizer->name = _name;

	Device::GetDevice()->CreateRasterizerState(&_desc, &newRasterizer->pState);
	ResMap<Rasterizer>::map.insert({ _name, newRasterizer });
	return newRasterizer;
}

DepthStencil* Resource::CreateDepthStencil(const char* _name, D3D11_DEPTH_STENCIL_DESC _desc)
{
	DepthStencil* newDepthStencil = new DepthStencil();
	newDepthStencil->name = _name;

	Device::GetDevice()->CreateDepthStencilState(&_desc, &newDepthStencil->pState);

	ResMap<DepthStencil>::map.insert({ _name, newDepthStencil });
	return newDepthStencil;
}

Texture* Resource::CreateTexture(const char* _path)
{
	EngineDirectory dir;
	dir.GoChild("Assets");
	dir.GoChild(_path);
	dir.Normalize();
	EngineString path = dir.GetString();

	EngineFile file;
	file.SetPath(path.c_str());
	EngineString filename = file.GetFileName();
	const char* name = filename.c_str();

	Texture* result = ResMap<Texture>::Find(name);
	if (result != nullptr)
	{
		return result;
	}

	wchar_t* wideStr;
	path.GetUTF8(&wideStr);

	Texture* newTex = new Texture();
	EngineString ext = file.GetExt();

	if (ext == ".dds")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wideStr, DirectX::DDS_FLAGS_NONE, &newTex->metaData, newTex->scratchImage))
		{
			Debug::MsgBoxAssert("파일경로가 불일치합니다.");
		}
	}
	else if (ext == ".png")
	{
		if (S_OK != DirectX::LoadFromWICFile(wideStr, DirectX::WIC_FLAGS_NONE, &newTex->metaData, newTex->scratchImage))
		{
			Debug::MsgBoxAssert("파일경로가 불일치합니다.");
		}
	}
	else if (ext == ".tga")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wideStr, &newTex->metaData, newTex->scratchImage))
		{
			Debug::MsgBoxAssert("파일경로가 불일치합니다.");
		}
	}

	delete[] wideStr;
	

	if (S_OK != DirectX::CreateShaderResourceView(Device::GetDevice(), newTex->scratchImage.GetImages(),
		newTex->scratchImage.GetImageCount(), newTex->metaData, &newTex->pShaderResourceView))
	{
		Debug::MsgBoxAssert("SRV생성 실패.");
	}


	ResMap<Texture>::map.insert({ name, newTex });
	newTex->name = name;
	return newTex;
}

Sampler* Resource::CreateSampler(const char* _name, D3D11_SAMPLER_DESC _desc)
{
	Sampler* newSampler = new Sampler();
	newSampler->name = _name;

	Device::GetDevice()->CreateSamplerState(&_desc, &newSampler->pState);

	ResMap<Sampler>::map.insert({ _name, newSampler });
	return newSampler;
}

ConstantBuffer* Resource::CreateConstantBuffer(const char* _name, void* _pData, int _dataSize, ShaderType _type)
{
	ConstantBuffer* newCB = new ConstantBuffer();
	newCB->name = _name;
	newCB->Type = _type;
	newCB->SetContext(Device::GetContext());

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = _dataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	newCB->pData = _pData;
	newCB->dataSize = _dataSize;
	Device::GetDevice()->CreateBuffer(&desc, nullptr, &newCB->pBuffer);

	ResMap<ConstantBuffer>::map.insert({ _name, newCB });
	return newCB;
}

Blend* Resource::CreateBlend(const char* _name, D3D11_BLEND_DESC _desc)
{
	Blend* newBlend = new Blend();
	newBlend->name = _name;

	Device::GetDevice()->CreateBlendState(&_desc, &newBlend->pState);

	ResMap<Blend>::map.insert({ _name, newBlend });
	return newBlend;
}

Mesh* Resource::CreateMesh(const char* _name)
{
	Mesh* newMesh = new Mesh();
	newMesh->name = _name;

	newMesh->SetContext(Device::GetContext());

	ResMap<Mesh>::map.insert({ _name, newMesh });
	return newMesh;
}

Material* Resource::CreateMaterial(const char* _name)
{
	Material* newMaterial = new Material();
	newMaterial->name = _name;

	newMaterial->SetContext(Device::GetContext());

	ResMap<Material>::map.insert({ _name, newMaterial });
	return newMaterial;
}