#pragma once
#include "D3D11API.h"

class Device;
class ResManager : public IResManager
{
public:
	ResManager();
	~ResManager();

	void* CreateResource(IDevice* DevicePtr, ResType _Type, EngineString _Name) override;
	void* Find(ResType _Type, const char* _Name) override;
    IInputLayout* FindIA(IDevice* DevicePtr, IMesh* _Mesh, IMaterial* _Material) override;
private:
	EngineHashMap ResourceMap;
};