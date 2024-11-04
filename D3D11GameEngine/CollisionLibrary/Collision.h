#pragma once
#include "ICollision.h"

class CCollision : public ICollision
{
public:
	CCollision();
	~CCollision();
	void SetType(COLLISION_TYPE type) override;
	COLLISION_TYPE GetType() const { return m_type; }
	void* Get3DShape() { return m_shape; }
	void UpdateTransform(XMVECTOR& position, XMVECTOR& scale, XMVECTOR& rotation) override;
private:
	void* m_shape = nullptr;
	COLLISION_TYPE m_type = COLLISION_TYPE::AABB;
};