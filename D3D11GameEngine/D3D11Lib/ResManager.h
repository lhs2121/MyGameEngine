#pragma once
#include "D3D11API.h"

class Device;
class ResManager : public IResManager
{
public:
	ResManager();
	~ResManager();

	void CreateDevice(IDevice** ppIDevice) override;
	void* CreateResource(ResType _Type, EngineString _Name) override;
	void* Find(ResType _Type, const char* _Name) override;
    IInputLayout* GenerateInputLayout(IMesh* _Mesh, IMaterial* _Material) override;
private:
	Device* DevicePtr;
	EngineHashMap ResourceMap;
};