#pragma once

#ifdef CollisionLibrary
#define CollisionAPI __declspec(dllexport)
#else
#define CollisionAPI __declspec(dllimport)
#endif


enum COLLISION_TYPE
{
	AABB2D = 1 << 0,
	SPHERE2D = 1 << 1,
	OBB2D = 1 << 2,
	AABB3D = 1 << 3,
	SPHERE3D = 1 << 4,
	OBB3D = 1 << 5,
};

struct ICollision
{
	virtual void SetType(COLLISION_TYPE type) = 0;
};

extern "C" CollisionAPI void CreateCollision(ICollision** ppCol);
extern "C" CollisionAPI bool Collision(ICollision* pLeft, ICollision* pRight);

