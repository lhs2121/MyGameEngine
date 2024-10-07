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

class ColGroup;
class Renderer;
class Colider : public Object
{
public:
	~Colider();

	void Awake() override;
	void Update(float _deltaTime) override;
	void Release() override;

	void SetCollisionType(CollisionType _Type);

	template<typename T>
	void SetColOrder(T _order);
	void SetColOrder(int _order);

	template<typename T>
	void Collision(T _otherOrder);
	void Collision(int _otherOrder);

	bool Search(Colider* _other);

	int colOrder;
	bool enter = false;
	bool stay = false;
	bool exit = false;
	bool free = false;
	Shape* shape = nullptr;
	CollisionType collisionType = CollisionType::_AABB;
	ColGroup* parentGroup;
	float4 debugColor = { 0,1,0,1 };
	std::unordered_map<Colider*, bool> otherCols;
private:
	Renderer* debugRenderer;
};

template<typename T>
inline void Colider::SetColOrder(T _order)
{
	SetColOrder((int)_order);
}

template<typename T>
inline void Colider::Collision(T _otherOrder)
{
	Collision((int)_otherOrder);
}
