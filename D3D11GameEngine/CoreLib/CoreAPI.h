#pragma once

struct IEngineD3DManager;
struct IEngineWindow;
class EngineString;
class float4;
struct ICamera;
enum class ProjectionType;

struct ICore
{
	virtual void                 EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, EngineObject* _CoreObject) = 0;

	virtual void                 EngineUpdate() = 0;

	virtual void                 EngineRelease() = 0;

	virtual ID3D11Device*        GetDevice() = 0;

	virtual ID3D11DeviceContext* GetContext() = 0;

	virtual IEngineWindow*       GetMainWindow() = 0;

	virtual IEngineD3DManager*   GetMainD3DManager() = 0;

	virtual EngineLevel*         CreateLevel(const char* _Name, EngineLevel* _NewLevel) = 0;

	virtual void                 ChangeLevel(const char* _Name) = 0;

	virtual void                 DeleteAllLevel() = 0;

	virtual bool                 IsDown(int KeyCode) = 0;

	virtual bool                 IsPress(int KeyCode) = 0;

	virtual bool                 IsUp(int KeyCode) = 0;
	    
	virtual bool                 IsFree(int KeyCode) = 0;
};

extern "C" CoreAPI void CreateEngineCore(ICore** pICore);

struct ILevel
{
	virtual void* CreateActor(const char* _Name, void* _NewActor) = 0;
		virtual ICamera* GetMainCamera() = 0;
};

struct ICamera
{
	void* CreateActor(const char* _Name, void* _NewActor);
	EngineObject* GetMainCamera();
};