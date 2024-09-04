#include "Pre.h"
#include "D3D11API.h"
#include "ResManager.h"
#include "Device.h"

void CreateDevice(IDevice** ppIDevice)
{
	*ppIDevice = new Device();
}

void DeleteDevice(IDevice* pIDevice)
{
	Device* castPtr = (Device*)pIDevice;
	delete castPtr;
}

void CreateResManager(IResManager** ppIResManager)
{
	*ppIResManager = new ResManager();
}

void DeleteResManager(IResManager* pIResManager)
{
	ResManager* castPtr = (ResManager*)pIResManager;
	delete castPtr;
}
	