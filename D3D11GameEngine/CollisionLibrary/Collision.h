#pragma once
#include "ICollision.h"

class CCollision : public ICollision
{
public:
	~CCollision();
	void SetType(COLLISION_TYPE type) override;
	void UpdateCollision(float x, float y, float width, float height);
	COLLISION_TYPE GetType() const { return m_type; }
	void* Get3DShape() { return m_3dShape; }
	float m_x;
	float m_y;
	float m_width;
	float m_height;
private:
	void* m_3dShape = nullptr;
	COLLISION_TYPE m_type = COLLISION_TYPE::AABB2D;
};