#include "Pre.h"
#include "ResourceAPI.h"
#include "DeviceManager.h"

void Device::Create(HWND* pHwnd, float4 WindowSize)
{
	if (DeviceManager::Inst != nullptr)
	{
		Debug::MsgBoxAssert("이미 생성된 클래스가 존재합니다.");
	}
	DeviceManager* deviceManager = new DeviceManager();
	deviceManager->Init(pHwnd, WindowSize);
}

void Device::Delete()
{
	if (DeviceManager::Inst != nullptr)
	{
		delete DeviceManager::Inst;
		DeviceManager::Inst = nullptr;
	}
}

void Device::InitMesh()
{
	return  DeviceManager::Inst->InitMesh();
}

void Device::InitMaterial()
{
	return  DeviceManager::Inst->InitMaterial();
}

void Device::Clear()
{
	return  DeviceManager::Inst->Clear();
}

void Device::Present()
{
	return  DeviceManager::Inst->Present();
}

ID3D11Device* Device::GetDevice()
{
	return DeviceManager::Inst->mainDevice;
}

ID3D11DeviceContext* Device::GetContext()
{
	return DeviceManager::Inst->mainContext;
}

void Device::SetClearColor(float4 _clearColor)
{
	DeviceManager::Inst->clearColor[0] = _clearColor.r;
	DeviceManager::Inst->clearColor[1] = _clearColor.g;
	DeviceManager::Inst->clearColor[2] = _clearColor.b;
	DeviceManager::Inst->clearColor[3] = _clearColor.a;
}
