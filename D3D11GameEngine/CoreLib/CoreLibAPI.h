#pragma once
#include "dllExport.h"
#include "d3d11.h"

struct IEngineD3DManager;
struct IEngineWindow;
struct IRenderer;
struct IObject;
struct ILevel;
class EngineString;
class float4;

enum class ProjectionType;

struct ICore
{
	virtual void                 EngineStart(const char* _WindowTitle, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IObject* _CoreObject) = 0;

	virtual void                 EngineUpdate() = 0;

	virtual void                 EngineRelease() = 0;

	virtual ID3D11Device*        GetDevice() = 0;

	virtual ID3D11DeviceContext* GetContext() = 0;

	virtual IEngineWindow*       GetMainWindow() = 0;

	virtual IEngineD3DManager*   GetMainD3DManager() = 0;

	virtual ILevel*              CreateLevel(const char* _Name, ILevel* _NewLevel) = 0;

	virtual void                 ChangeLevel(const char* _Name) = 0;

	virtual void                 DeleteAllLevel() = 0;

	virtual bool                 IsDown(int KeyCode) = 0;

	virtual bool                 IsPress(int KeyCode) = 0;

	virtual bool                 IsUp(int KeyCode) = 0;
	 
	virtual bool                 IsFree(int KeyCode) = 0;
};

extern "C" CoreAPI void CreateEngineCore(ICore * *pICore, const char* _Tilte, float4 _WindowPos, float4 _WindowSize, HINSTANCE _hInstance, IObject * _ContentsObject);

struct IObject
{
	virtual void     SetName(IObject _Name) = 0;

	virtual void     SetParent(IObject* _Parent) = 0;

	virtual void     DetachParent() = 0;

	virtual void     SetChild(IObject* _Child) = 0;

	virtual void     DetachChild(IObject* _Child) = 0;

	virtual IObject* GetChild(int Order) = 0;

	virtual IObject* GetTopParent() = 0;

	virtual void     Destroy() = 0;

	virtual bool     IsDeath() = 0;

	virtual void     Start() = 0;

	virtual void     ChildUpdate(float _Delta) = 0;

	virtual void     Update(float _Delta) = 0;

	virtual void     Release() = 0;
};

struct ILevel : public IObject
{
	virtual IObject* CreateActor(IObject* _NewActor) = 0;
	virtual IObject* GetMainCamera() = 0;
};

// 레벨 오브젝트 (레벨이 관리)
struct ILevelObject : public IObject
{
	virtual ILevel* GetLevel() = 0;
};

struct IActor : public ILevelObject
{
	virtual IObject* CreateComponent(IObject* _NewActor) = 0;
};

struct ICamera : public ILevelObject
{
	virtual void Start() = 0;
	virtual void Update(float _Delta) = 0;
	virtual void PushRenderer(IRenderer* Renderer) = 0;
	virtual void SetProjectionType(ProjectionType _Type) = 0;
	virtual void Render() = 0;
};

// 컴포넌트 (액터가 관리)
struct IComponent : public ILevelObject
{

};

struct IRenderer : public IComponent
{
	virtual void Render() = 0;
	virtual void SetTexture(EngineString _Name) = 0;
	virtual void SetSampler(EngineString _Name) = 0;
};

struct ISpriteRenderer : public IRenderer
{
	virtual void CreateAnimation(int _SpriteCountX, int _SpriteCountY, float _InterTime) = 0;
};


