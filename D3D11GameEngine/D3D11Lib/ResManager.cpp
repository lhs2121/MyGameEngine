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
#include "VertexFormat.h"
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
}

void* ResManager::CreateResource(IDevice* DevicePtr, ResType _Type, EngineString _Name)
{
	IResBase* Res = nullptr;
	EngineString Name;

	switch (_Type)
	{
	case ResType::Mesh:
	{
		Name += "Mesh_";

		Mesh* MeshPtr = new Mesh();
		MeshPtr->ContextPtr = DevicePtr->GetContext();
		MeshPtr->ManagerPtr = this;

		Res = MeshPtr;
		break;
	}
	case ResType::Material:
	{
		Name += "Material_";

		Material* MaterialPtr = new Material();
		MaterialPtr->ContextPtr = DevicePtr->GetContext();
		MaterialPtr->ManagerPtr = this;

		Res = MaterialPtr;

		break;
	}
	case ResType::VB:
		Name += "VB_";
		Res = new VertexBuffer();
		break;
	case ResType::IB:
		Name += "IB_";
		Res = new IndexBuffer();
		break;
	case ResType::CB:
		Name += "CB_";
		Res = new ConstantBuffer();
		break;
	case ResType::IA:
		Name += "IA_";
		Res = new InputLayout();
		break;
	case ResType::VS:
		Name += "VS_";
		Res = new VertexShader();
		break;
	case ResType::PS:
		Name += "PS_";
		Res = new PixelShader();
		break;
	case ResType::RS:
		Name += "RS_";
		Res = new Rasterizer();
		break;
	case ResType::DS:
		Name += "DS_";
		Res = new DepthStencil();
		break;
	case ResType::Sampler:
		Name += "Sampler_";
		Res = new Sampler();
		break;
	case ResType::Texture:
		Name += "Texture_";
		Res = new Texture();
		break;
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

IInputLayout* ResManager::FindIA(IDevice* DevicePtr, IMesh* _Mesh, IMaterial* _Material)
{
	VertexShader* VSPtr = (VertexShader*)_Material->GetVS();
	EngineString Name = VSPtr->GetLayoutName();
	std::vector<EngineString> Sementics = VSPtr->GetSementics();

	InputLayout* Result = (InputLayout*)Find(ResType::IA, Name.c_str());
	if (Result == nullptr)
	{
		Result = (InputLayout*)CreateResource(DevicePtr, ResType::IA, Name);
		Result->Setting(DevicePtr->GetDevice(), _Mesh->GetVB(), _Material->GetVS());
	}

	return Result;
}