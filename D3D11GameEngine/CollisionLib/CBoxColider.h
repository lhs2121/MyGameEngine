#pragma once
#include "CollisionAPI.h"

class CBoxColider : public IBoxColider
{
public:
	void SetTransform(Transform& _transform) override;
	bool Collision(IBoxColider* pCol) override;
	bool Collision(IOriBoxColider* pCol) override;
	bool Collision(ISphereColider* pCol) override;

	DirectX::BoundingBox* m_AABB = nullptr;
};

