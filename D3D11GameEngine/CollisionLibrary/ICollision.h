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

extern "C" CollisionAPI void CreateCollision(ICollision** ppCol);
extern "C" CollisionAPI void DeleteCollision(ICollision* pCol);
extern "C" CollisionAPI bool Collision(ICollision* pLeft, ICollision* pRight);
