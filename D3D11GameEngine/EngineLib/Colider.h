#pragma once
#include "Object.h"
#include <DirectXCollision.h>

struct Shape
{
	virtual void Update(Transform& _transform) = 0;
};

struct AABB : public Shape
{
	DirectX::BoundingBox box;
	void Update(Transform& _transform) override
	{
		XMStoreFloat3(&box.Center, _transform.vecWorldPosition);
		XMStoreFloat3(&box.Extents, _transform.vecWorldScale/2);
	}
};

struct SPHERE : public Shape
{
	DirectX::BoundingSphere sphere;
	void Update(Transform& _transform) override
	{
		XMStoreFloat3(&sphere.Center, _transform.vecWorldPosition);
		XMStoreFloat(&sphere.Radius, _transform.vecWorldScale / 2);
	}
};

struct OBB : public Shape
{
	DirectX::BoundingOrientedBox box;
	void Update(Transform& _transform) override
	{
		XMStoreFloat3(&box.Center, _transform.vecWorldPosition);
		XMStoreFloat3(&box.Extents, _transform.vecWorldScale / 2);
		XMStoreFloat4(&box.Orientation, _transform.quatWorld);
	}
};

enum CollisionType
{
	_AABB = 1,
	_SPHERE = 2,
	_OBB = 4,
};

class CQuadTree;
class Renderer;
class Colider : public Object
{
public:
	Colider();
	~Colider();

	void Awake() override;
	void Update(float _deltaTime) override;

	void SetCollisionType(CollisionType _Type);
	bool Collision(Colider* pOther);
	bool SimpleCollision(Colider* pOther);
	bool Search(Colider* _other);

private:
	bool AABBvsAABB(AABB* _aabb1, AABB* _aabb2) const;
	bool AABBvsSPHERE(AABB* _aabb, SPHERE* _sphere);
	bool AABBvsOBB(AABB* _aabb, OBB* _obb);
	bool OBBvsOBB(OBB* _obb1, OBB* _obb2);
	bool OBBvsSPHERE(OBB* _obb, SPHERE* _sphere);
	bool SPHEREvsSPHERE(SPHERE* _sphere1, SPHERE* _sphere2) const;

	Shape* shape = nullptr;
	CollisionType collisionType = CollisionType::_AABB;
	float4 debugColor = { 0,1,0,1 };
	std::unordered_map<Colider*, bool> otherCols;
	Renderer* debugRenderer;
};

