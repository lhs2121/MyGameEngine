#include "Pre.h"
#include "ResourceAPI.h"
#include "DeviceManager.h"

void Device::Create(HWND* pHwnd, float4 WindowSize)
{
	if (DeviceManager::Inst != nullptr)
	{
		Debug::MsgBoxAssert("�̹� ������ Ŭ������ �����մϴ�.");
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