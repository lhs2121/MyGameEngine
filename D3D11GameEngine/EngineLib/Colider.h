#pragma once
#include "Object.h"
#include <DirectXCollision.h>
struct Shape
{
	const char* name;
	virtual void Update(Transform& _transform) = 0;
};
struct AABB2D : public Shape
{
	DirectX::BoundingOrientedBox box;
	void Update(Transform& _transform) override
	{
		XMStoreFloat3(&box.Center, _transform.worldPosition);
		box.Extents.x = _transform.worldScale.m128_f32[0] / 2;
		box.Extents.y = _transform.worldScale.m128_f32[1] / 2;
	}
};

struct SPHERE2D : public Shape
{
	DirectX::BoundingSphere sphere;

	void Update(Transform& _transform) override
	{
		XMStoreFloat3(&sphere.Center, _transform.worldPosition);
		sphere.Radius = _transform.worldScale.m128_f32[0] / 2;;
	}
};

struct OBB2D : public Shape
{
	DirectX::BoundingOrientedBox box;
	void Update(Transform& _transform) override
	{
		XMStoreFloat3(&box.Center, _transform.worldPosition);
		//box.Center.z = 0;
	
		box.Extents.x = _transform.worldScale.m128_f32[0] / 2;
		box.Extents.y = _transform.worldScale.m128_f32[1] / 2;
		box.Extents.z = 0;
	
		XMStoreFloat4(&box.Orientation, _transform.worldQuaternion);
	}
};

enum ColType
{
	_AABB2D = 1,
	_SPHERE2D = 2,
	_OBB2D = 4,
	_AABB3D,
	_SPHERE3D,
	_OBB3D,
};

enum class ColState
{
	FREE,
	ENTER,
	STAY,
	EXIT
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

	void SetColType(ColType _Type);

	template<typename T>
	void SetColOrder(T _order);

	void SetColOrder(int _order);

	template<typename T>
	void Collision(T _otherOrder);
	void Collision(int _otherOrder);

	bool Search(Colider* _other);

	int colOrder;
	Shape* shape = nullptr;
	ColState state = ColState::FREE;
	ColType colType = ColType::_AABB2D;
	ColGroup* parentGroup;

	float4 debugColor = { 0,1,0,1 };

	std::list<Colider*> otherColiders;
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
