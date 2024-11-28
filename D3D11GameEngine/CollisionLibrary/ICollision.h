#pragma once

#ifdef CollisionLibrary
#define CollisionAPI __declspec(dllexport)
#else
#define CollisionAPI __declspec(dllimport)
#endif

#include <DirectXMath.h>
#include <EngineLib/Transform.h>
using namespace DirectX;
struct IRenderer;
enum COLLISION_TYPE
{
	AABB = 1 << 0,
	SPHERE = 1 << 1,
	OBB = 1 << 2,
};

struct ICollision
{
	virtual void UpdateTransform(Transform* pTransform) = 0;
	virtual void SetType(COLLISION_TYPE type) = 0;
};

struct IQuadTree
{
	virtual void Initialize(float posX, float posY, float width, float height, int maxlevel, IRenderer* pRenderer) = 0;
	virtual void Clear() = 0;
	virtual void Insert(ICollision* pCol) = 0;
	virtual void DebugRender() = 0;
};

extern "C" CollisionAPI void CreateQuadTree(IQuadTree** ppQuad);
extern "C" CollisionAPI void DeleteQuadTree(IQuadTree* pQuad);

extern "C" CollisionAPI void CreateCollision(ICollision** ppCol);
extern "C" CollisionAPI void DeleteCollision(ICollision* pCol);
extern "C" CollisionAPI bool Collision(ICollision* pLeft, ICollision* pRight);

