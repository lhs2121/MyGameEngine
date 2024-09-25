#pragma once
#include "Object.h"

struct Shape
{
	virtual void Update(Transform& _transform) = 0;
};
struct AABB2D : public Shape
{
	float4 center;

	float left;
	float right;
	float top;
	float bottom;

	void Update(Transform& _transform) override
	{
		center = _transform.worldPosition;
		right = _transform.worldPosition.x + _transform.worldScale.hx();
		left = _transform.worldPosition.x - _transform.worldScale.hx();
		top = _transform.worldPosition.y + _transform.worldScale.hy();
		bottom = _transform.worldPosition.y - _transform.worldScale.hy();
	}
};

struct SPHERE2D : public Shape
{
	float4 center;

	float radius;

	void Update(Transform& _transform) override
	{
		center = _transform.worldPosition;
		radius = _transform.worldScale.hx();
	}
};

struct OBB2D : public Shape
{
	float4 center;

	float left;
	float right;
	float top;
	float bottom;

	void Update(Transform& _transform) override
	{
		center = _transform.worldPosition;
		right = _transform.worldPosition.x + _transform.worldScale.hx();
		left = _transform.worldPosition.x - _transform.worldScale.hx();
		top = _transform.worldPosition.y + _transform.worldScale.hy();
		bottom = _transform.worldPosition.y - _transform.worldScale.hy();
	}
};

enum class ColType
{
	AABB2D,
	AABB3D,
	OBB2D,
	OBB3D,
	SPHERE2D,
	SPHERE3D
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
	ColType colType = ColType::AABB2D;
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
