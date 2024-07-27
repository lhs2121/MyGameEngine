#pragma once
#include "D3D11API.h"

class EngineDevice;
class EngineD3DManager : public IEngineD3DManager
{
public:
	IEngineDevice* CreateDevice() override;
	void  CleanUp();
	void* CreateResource(ResType _Type, EngineString _Name) override;
	void* Find(ResType _Type, const char* _Name) override;
private:
	EngineDevice* EngineDevicePtr = nullptr;
	EngineHashMap ResourceMap;
};