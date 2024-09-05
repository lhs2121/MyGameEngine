#include "Pre.h"
#include "ResManager.h"
#include "Device.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Rasterizer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DepthStencil.h"
#include "Texture.h"
#include "Sampler.h"
#include "ConstantBuffer.h"
#include "Mesh.h"
#include "Material.h"

ResManager::ResManager()
{
}

ResManager::~ResManager()
{
	ResourceMap.GoFirst();
	UINT Count = ResourceMap.Count();
	for (size_t i = 0; i < Count; i++)
	{
		IResBase* CurItem = (IResBase*)ResourceMap.GetCurItem();
		delete CurItem;
		ResourceMap.GoNext();
	}

	if (DevicePtr != nullptr)
	{
		delete DevicePtr;
	}

}

void ResManager::CreateDevice(IDevice** ppIDevice)
{
	DevicePtr = new Device();
	*ppIDevice = DevicePtr;
}

void* ResManager::CreateResource(ResType _Type, EngineString _Name)
{
	IResBase* Res = nullptr;
	EngineString Name;

	switch (_Type)
	{
	case ResType::Mesh:
	{
		Name += "Mesh_";

		Mesh* NewRes = new Mesh();
		NewRes->ManagerPtr = this;
		Res = NewRes;
		break;
	}
	case ResType::Material:
	{
		Name += "Material_";

		Material* NewRes = new Material();
		NewRes->ManagerPtr = this;
		Res = NewRes;
		break;
	}
	case ResType::VB:
	{
		Name += "VB_";

		VertexBuffer* NewRes = new VertexBuffer();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	case ResType::IB:
	{
		Name += "IB_";

		IndexBuffer* NewRes = new IndexBuffer();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	case ResType::CB:
	{
		Name += "CB_";

		ConstantBuffer* NewRes = new ConstantBuffer();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	case ResType::IA:
	{
		Name += "IA_";

		InputLayout* NewRes = new InputLayout();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	case ResType::VS:
	{
		Name += "VS_";

		VertexShader* NewRes = new VertexShader();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	case ResType::PS:
	{
		Name += "PS_";

		PixelShader* NewRes = new PixelShader();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	case ResType::RS:
	{
		Name += "RS_";

		Rasterizer* NewRes = new Rasterizer();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;

	}
	case ResType::DS:
	{
		Name += "DS_";

		DepthStencil* NewRes = new DepthStencil();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	case ResType::Sampler:
	{
		Name += "Sampler_";

		Sampler* NewRes = new Sampler();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;

	}
	case ResType::Texture:
	{
		Name += "Texture_";

		Texture* NewRes = new Texture();
		NewRes->DevicePtr = DevicePtr->GetDevice();
		NewRes->ContextPtr = DevicePtr->GetContext();
		Res = NewRes;
		break;
	}
	}

	Name += _Name;
	ResourceMap.Add(Name, Res);
	return Res;
}

void* ResManager::Find(ResType _Type, const char* _Name)
{
	EngineString Name;

	switch (_Type)
	{
	case ResType::Mesh:
		Name += "Mesh_";
		break;
	case ResType::Material:
		Name += "Material_";
		break;
	case ResType::VB:
		Name += "VB_";
		break;
	case ResType::IB:
		Name += "IB_";
		break;
	case ResType::CB:
		Name += "CB_";
		break;
	case ResType::IA:
		Name += "IA_";
		break;
	case ResType::VS:
		Name += "VS_";
		break;
	case ResType::PS:
		Name += "PS_";
		break;
	case ResType::RS:
		Name += "RS_";
		break;
	case ResType::DS:
		Name += "DS_";
		break;
	case ResType::Sampler:
		Name += "Sampler_";
		break;
	case ResType::Texture:
		Name += "Texture_";
		break;
	default:
		break;
	}
	Name += _Name;
	return ResourceMap.Get(Name.c_str());;
}

IInputLayout* ResManager::GenerateInputLayout(IMesh* _Mesh, IMaterial* _Material)
{
	VertexShader* VSPtr = (VertexShader*)_Material->GetVS();
	EngineString Name = VSPtr->GetLayoutName();
	std::vector<EngineString> Sementics = VSPtr->GetSementics();

	InputLayout* Result = (InputLayout*)Find(ResType::IA, Name.c_str());
	if (Result == nullptr)
	{
		Result = (InputLayout*)CreateResource(ResType::IA, Name);
		Result->Setting(_Mesh->GetVB(), _Material->GetVS());
	}

	return Result;
}