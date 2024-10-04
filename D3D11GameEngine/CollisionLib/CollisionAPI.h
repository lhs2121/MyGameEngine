#pragma once
#include <common/declspec.h>
#include <DirectXCollision.h>

struct IColiderGroup
{
	virtual void AddCollision() = 0;
	virtual void Collision(IColiderGroup* pColGroup) = 0;
};
class Transform;
struct IOriBoxColider;
struct ISphereColider;
struct IBoxColider 
{
	virtual bool Collision(IBoxColider* pCol) = 0;
	virtual bool Collision(IOriBoxColider* pCol) = 0;
	virtual bool Collision(ISphereColider* pCol) = 0;
	virtual void SetTransform(Transform& _transform) = 0;
};

struct IOriBoxColider
{
	virtual bool Collision(IBoxColider* pCol) = 0;
	virtual bool Collision(IOriBoxColider* pCol) = 0;
	virtual bool Collision(ISphereColider* pCol) = 0;
	virtual void SetTransform(Transform& _transform) = 0;
};

struct ISphereColider
{
	virtual bool Collision(IBoxColider* pCol) = 0;
	virtual bool Collision(IOriBoxColider* pCol) = 0;
	virtual bool Collision(ISphereColider* pCol) = 0;
	virtual void SetTransform(Transform& _transform) = 0;
};

extern "C" CollisionAPI void CreateBoxColider(IBoxColider** ppCol);
extern "C" CollisionAPI void DeleteBoxColider(IBoxColider* pCol);

extern "C" CollisionAPI void CreateOriBoxColider(IOriBoxColider** ppCol);
extern "C" CollisionAPI void DeleteOriBoxColider(IOriBoxColider* pCol);

extern "C" CollisionAPI void CreateSphereColider(ISphereColider** ppCol);
extern "C" CollisionAPI void DeleteSphereColider(ISphereColider* pCol);