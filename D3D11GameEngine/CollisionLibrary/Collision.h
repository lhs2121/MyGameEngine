#pragma once
#include "ICollision.h"

class CCollision : public ICollision
{
public:
	CCollision();
	~CCollision();
	void SetType(COLLISION_TYPE type) override;
	COLLISION_TYPE GetType() const { return m_type; }
	void UpdateTransform(Transform* pTransform);
	void UpdateTransform(XMVECTOR& vecPos, XMVECTOR& vecScale, XMVECTOR& vecRot);
	void* GetShape() { return m_pShape; }

private:
	void* m_pShape = nullptr;
	COLLISION_TYPE m_type = COLLISION_TYPE::AABB;
};