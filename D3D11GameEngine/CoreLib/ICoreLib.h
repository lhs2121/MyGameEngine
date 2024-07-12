#pragma once
#include "CoreAPI.h"

struct IRenderer;
class EngineString;
enum class ProjectionType;
struct IObject
{
	virtual void SetName(IObject _Name)            = 0;
	virtual void SetParent(IObject* _Parent)       = 0;
	virtual void DetachParent()                    = 0;
	virtual void SetChild(IObject* _Child)         = 0;
	virtual void DetachChild(IObject* _Child)      = 0;
	virtual IObject* GetChild(int Order)           = 0;
	virtual IObject* GetTopParent()                = 0;
	virtual void Destroy()                         = 0;
	virtual bool IsDeath()                         = 0;
	virtual void Start()                           = 0;
	virtual void ChildUpdate(float _Delta)         = 0;
	virtual void Update(float _Delta)              = 0;
	virtual void Release()                         = 0;
};

struct ILevel : public IObject
{
	virtual IObject* CreateActor(int _ActorSize, IObject* _NewActor) = 0;
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
	virtual void Start() override = 0;
	virtual void Update(float _Delta) override = 0;
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


