#pragma once
#include "Interface.h"
#include "RendererLibrary/Interface.h"

class CCollision : public ICollision
{
public:
	CCollision();
	~CCollision();
	void SetType(COLLISION_TYPE type) override;
	COLLISION_TYPE GetType() const { return m_type; }
	void UpdateTransform(FXMVECTOR scale, FXMVECTOR rot, FXMVECTOR pos);
	void* GetShape() { return m_pShape; }

private:
	void* m_pShape = nullptr;
	COLLISION_TYPE m_type = COLLISION_TYPE::AABB;
};