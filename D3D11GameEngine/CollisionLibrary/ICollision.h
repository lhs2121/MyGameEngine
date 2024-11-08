#pragma once

#ifdef CollisionLibrary
#define CollisionAPI __declspec(dllexport)
#else
#define CollisionAPI __declspec(dllimport)
#endif

#include <DirectXMath.h>
using namespace DirectX;

enum COLLISION_TYPE
{
	AABB = 1 << 0,
	SPHERE = 1 << 1,
	OBB = 1 << 2,
};

struct ICollision
{
	virtual void SetType(COLLISION_TYPE type) = 0;
	virtual void UpdateTransform(XMVECTOR& position, XMVECTOR& scale, XMVECTOR& rotation) = 0;
};

struct IQuadTree
{
	virtual void Initialize(float posX, float posY, float width, float height, int maxlevel) = 0;
	virtual void UpdateCollision(ICollision* pCol) = 0;
};

extern "C" CollisionAPI void CreateQuadTree(IQuadTree** ppQuad);
extern "C" CollisionAPI void DeleteQuadTree(IQuadTree* pQuad);

extern "C" CollisionAPI void CreateCollision(ICollision** ppCol);
extern "C" CollisionAPI void DeleteCollision(ICollision* pCol);
extern "C" CollisionAPI bool Collision(ICollision* pLeft, ICollision* pRight);

