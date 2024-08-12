#include "Pre.h"
#include "EngineD3DManager.h"
#include "EngineDevice.h"
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
#include "EngineMesh.h"
#include "EngineMaterial.h"

EngineD3DManager* EngineD3DManager::MainManager = nullptr;

EngineD3DManager::EngineD3DManager()
{
	MainManager = this;
}

EngineD3DManager::~EngineD3DManager()
{
	ResourceMap.GoFirst();
	UINT Count = ResourceMap.Count();
	for (size_t i = 0; i < Count; i++)
	{
		IEngineUnknown* CurItem = (IEngineUnknown*)ResourceMap.GetCurItem();
		delete CurItem;
		ResourceMap.GoNext();
	}

	if (EngineDevicePtr != nullptr)
	{
		delete EngineDevicePtr;
		EngineDevicePtr = nullptr;
	}
}

IEngineDevice* EngineD3DManager::CreateDevice()
{
	EngineDevicePtr = new EngineDevice();

	IEngineDevice* NewDevice = EngineDevicePtr;
	return NewDevice;
}

void* EngineD3DManager::CreateResource(ResType _Type, EngineString _Name)
{
	IEngineUnknown* NewResource = nullptr;
	EngineString ResourceName;

	switch (_Type)
	{
	case ResType::Mesh:
		ResourceName += "Mesh_";
		NewResource = new EngineMesh();
		break;
	case ResType::Material:
		ResourceName += "Material_";
		NewResource = new EngineMaterial();
		break;
	case ResType::VB:
		ResourceName += "VB_";
		NewResource = new EngineVertexBuffer();
		break;
	case ResType::IB:
		ResourceName += "IB_";
		NewResource = new EngineIndexBuffer();
		break;
	case ResType::CB:
		ResourceName += "CB_";
		NewResource = new EngineConstantBuffer();
		break;
	case ResType::IA:
		ResourceName += "IA_";
		NewResource = new EngineInputLayout();
		break;
	case ResType::VS:
		ResourceName += "VS_";
		NewResource = new EngineVertexShader();
		break;
	case ResType::PS:
		ResourceName += "PS_";
		NewResource = new EnginePixelShader();
		break;
	case ResType::RS:
		ResourceName += "RS_";
		NewResource = new EngineRasterizer();
		break;
	case ResType::DS:
		ResourceName += "DS_";
		NewResource = new EngineDepthStencil();
		break;
	case ResType::Sampler:
		ResourceName += "Sampler_";
		NewResource = new EngineSampler();
		break;
	case ResType::Texture:
		ResourceName += "Texture_";
		NewResource = new EngineTexture();
		break;
	default:
		break;
	}

	NewResource->SetDevice(EngineDevicePtr->GetDevice());
	NewResource->SetContext(EngineDevicePtr->GetContext());

	ResourceName += _Name;
	ResourceMap.Add(ResourceName, NewResource);
	return NewResource;
}

void* EngineD3DManager::Find(ResType _Type, const char* _Name)
{
	EngineString ResourceName;

	switch (_Type)
	{
	case ResType::Mesh:
		ResourceName += "Mesh_";
		break;
	case ResType::Material:
		ResourceName += "Material_";
		break;
	case ResType::VB:
		ResourceName += "VB_";
		break;
	case ResType::IB:
		ResourceName += "IB_";
		break;
	case ResType::CB:
		ResourceName += "CB_";
		break;
	case ResType::IA:
		ResourceName += "IA_";
		break;
	case ResType::VS:
		ResourceName += "VS_";
		break;
	case ResType::PS:
		ResourceName += "PS_";
		break;
	case ResType::RS:
		ResourceName += "RS_";
		break;
	case ResType::DS:
		ResourceName += "DS_";
		break;
	case ResType::Sampler:
		ResourceName += "Sampler_";
		break;
	case ResType::Texture:
		ResourceName += "Texture_";
		break;
	default:
		break;
	}
	ResourceName += _Name;
	return ResourceMap.Get(ResourceName.c_str());;
}

IEngineInputLayout* EngineD3DManager::FindIA(IMesh* _Mesh, IMaterial* _Material)
{
	EngineVertexShader* vs = (EngineVertexShader*)_Material->GetVS();
	EngineString Sementics = vs->GetSementic();
	EngineInputLayout* layout = (EngineInputLayout * )Find(ResType::IA, Sementics.c_str());
	if (layout == nullptr)
	{
		CreateResource(ResType::IA, Sementics);
		layout->Setting(_Mesh->GetVB(), _Material->GetVS());
	}


	return layout;
}