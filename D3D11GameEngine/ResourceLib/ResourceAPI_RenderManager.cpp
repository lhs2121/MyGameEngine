#include "Pre.h"
#include "ResourceAPI.h"
#include "RenderManager.h"

void Device::Create(HWND* pHwnd, float4 WindowSize)
{
	if (RenderManager::Inst != nullptr)
	{
		Debug::MsgBoxAssert("이미 생성된 클래스가 존재합니다.");
	}
	RenderManager* renderManager = new RenderManager();
	renderManager->Init(pHwnd, WindowSize);
}

void Device::Delete()
{
	if (RenderManager::Inst != nullptr)
	{
		delete RenderManager::Inst;
		RenderManager::Inst = nullptr;
	}
}

void Device::InitMesh()
{
	return  RenderManager::Inst->InitMesh();
}

void Device::InitMaterial()
{
	return  RenderManager::Inst->InitMaterial();
}

void Device::Clear()
{
	return  RenderManager::Inst->Clear();
}

void Device::Present()
{
	return  RenderManager::Inst->Present();
}

ID3D11Device* Device::GetDevice()
{
	return RenderManager::Inst->mainDevice;
}

ID3D11DeviceContext* Device::GetContext()
{
	return RenderManager::Inst->mainContext;
}
