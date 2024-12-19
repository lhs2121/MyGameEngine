#pragma once

#ifdef COLLISIONLIBRARY_EXPORTS
#define COLLISIONLIBRARY_API __declspec(dllexport)
#else
#define COLLISIONLIBRARY_API __declspec(dllimport)
#endif

#include <DirectXMath.h>
#include <EngineLibrary/Transform.h>
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

extern "C" COLLISIONLIBRARY_API void CreateQuadTree(IQuadTree** ppQuad);
extern "C" COLLISIONLIBRARY_API void DeleteQuadTree(IQuadTree* pQuad);

extern "C" COLLISIONLIBRARY_API void CreateCollision(ICollision** ppCol);
extern "C" COLLISIONLIBRARY_API void DeleteCollision(ICollision* pCol);
extern "C" COLLISIONLIBRARY_API bool Collision(ICollision* pLeft, ICollision* pRight);

