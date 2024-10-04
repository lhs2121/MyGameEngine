#pragma once
#include "CollisionAPI.h"

class COriBoxColider : public IOriBoxColider
{
public:
	void SetTransform(Transform& _transform) override;
	bool Collision(IBoxColider* pCol) override;
	bool Collision(IOriBoxColider* pCol) override;
	bool Collision(ISphereColider* pCol) override;

	DirectX::BoundingOrientedBox* m_OBB = nullptr;
};