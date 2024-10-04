#pragma once
#include "CollisionAPI.h"

class CSphereColider : public ISphereColider
{
public:
	void SetTransform(Transform& _transform) override;
	bool Collision(IBoxColider* pCol) override;
	bool Collision(IOriBoxColider* pCol) override;
	bool Collision(ISphereColider* pCol) override;
	DirectX::BoundingSphere* m_Sphere = nullptr;
};
