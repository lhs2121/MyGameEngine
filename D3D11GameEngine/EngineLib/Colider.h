#pragma once
#include "Object.h"

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
	float left;
	float right;
	float top;
	float bottom;
	float radius;
	ColState state = ColState::FREE;
	ColType colType = ColType::AABB2D;
	ColGroup* parentGroup;

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
