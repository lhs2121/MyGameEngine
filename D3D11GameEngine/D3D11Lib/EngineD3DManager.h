#pragma once
#include "D3D11API.h"

class EngineDevice;
class EngineD3DManager : public IEngineD3DManager
{
public:
	static EngineD3DManager* MainManager;
	EngineD3DManager();
	~EngineD3DManager();

	IEngineDevice* CreateDevice() override;
	void* CreateResource(ResType _Type, EngineString _Name) override;
	void* Find(ResType _Type, const char* _Name) override;
    IEngineInputLayout* FindIA(IMesh* _Mesh, IMaterial* _Material) override;

private:
	EngineDevice* EngineDevicePtr = nullptr;
	EngineHashMap ResourceMap;
};