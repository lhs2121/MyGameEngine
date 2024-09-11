#include "Pre.h"
#include "ResourceAPI.h"
#include "ResourceContainer.h"
#include "Device.h"

Rasterizer* Resource::CreateRasterizer(const char* _name, D3D11_RASTERIZER_DESC _desc)
{
	Rasterizer* newRasterizer = new Rasterizer();
	newRasterizer->name = _name;

	Device::mainDevice->CreateRasterizerState(&_desc, &newRasterizer->pState);
	ResourceContainer<Rasterizer>::Resources.insert({ _name, newRasterizer });
	return newRasterizer;
}

DepthStencil* Resource::CreateDepthStencil(const char* _name, D3D11_DEPTH_STENCIL_DESC _desc)
{
	DepthStencil* newDepthStencil = new DepthStencil();
	newDepthStencil->name = _name;

	Device::mainDevice->CreateDepthStencilState(&_desc, &newDepthStencil->pState);

	ResourceContainer<DepthStencil>::Resources.insert({ _name, newDepthStencil });
	return newDepthStencil;
}

Texture* Resource::CreateTexture(const char* _path)
{
	char* name;


		name = (char*)_path;
		size_t len = strlen(_path);
		name += len;
		while (*name != '/')
		{
			name--;
		}
		name++;
	

	if (ResourceContainer<Texture>::Resources.find(name) != ResourceContainer<Texture>::Resources.end())
	{
		return ResourceContainer<Texture>::Find(name);
	}


	Texture* newTex = new Texture();

	int wideStrSize = MultiByteToWideChar(CP_ACP, 0, _path, -1, NULL, 0);
	wchar_t* wideStr = new wchar_t[wideStrSize];
	int result = MultiByteToWideChar(CP_ACP, 0, _path, -1, wideStr, wideStrSize);

	if (S_OK != DirectX::LoadFromWICFile(wideStr, DirectX::WIC_FLAGS_NONE, &newTex->metaData, newTex->scratchImage))
	{
		EngineDebug::MsgBoxAssert("파일경로가 불일치합니다.");
	}

	if (S_OK != DirectX::CreateShaderResourceView(Device::mainDevice, newTex->scratchImage.GetImages(),
		newTex->scratchImage.GetImageCount(), newTex->metaData, &newTex->pShaderResourceView))
	{
		EngineDebug::MsgBoxAssert("SRV생성 실패.");
	}

	delete[] wideStr;

	ResourceContainer<Texture>::Resources.insert({ name, newTex });
	newTex->name = name;
	return newTex;
}

Sampler* Resource::CreateSampler(const char* _name, D3D11_SAMPLER_DESC _desc)
{
	Sampler* newSampler = new Sampler();
	newSampler->name = _name;

	Device::mainDevice->CreateSamplerState(&_desc, &newSampler->pState);

	ResourceContainer<Sampler>::Resources.insert({ _name, newSampler });
	return newSampler;
}

ConstantBuffer* Resource::CreateConstantBuffer(const char* _name, void* _pData, int _dataSize, ShaderType _type)
{
	ConstantBuffer* newCB = new ConstantBuffer();
	newCB->name = _name;
	newCB->Type = _type;
	newCB->SetContext(Device::mainContext);

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = _dataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	newCB->pData = _pData;
	newCB->dataSize = _dataSize;
	Device::mainDevice->CreateBuffer(&desc, nullptr, &newCB->pBuffer);

	ResourceContainer<ConstantBuffer>::Resources.insert({ _name, newCB });
	return newCB;
}

Mesh* Resource::CreateMesh(const char* _name)
{
	Mesh* newMesh = new Mesh();
	newMesh->name = _name;

	newMesh->SetContext(Device::mainContext);

	ResourceContainer<Mesh>::Resources.insert({ _name, newMesh });
	return newMesh;
}

Material* Resource::CreateMaterial(const char* _name)
{
	Material* newMaterial = new Material();
	newMaterial->name = _name;

	newMaterial->SetContext(Device::mainContext);

	ResourceContainer<Material>::Resources.insert({ _name, newMaterial });
	return newMaterial;
}	