#pragma once
#include "Colider.h"
class ColGroup
{
	friend class Scene;
public:
	void Collision(Colider* _col, ColGroup* _group);

	bool AABB2DvsAABB2D(AABB2D* _aabb1, AABB2D* _aabb2) const;
	bool AABB2DvsSPHERE2D(AABB2D* _aabb, SPHERE2D* _sphere);
	bool AABB2DvsOBB2D(AABB2D* _aabb, OBB2D* _obb);

	bool OBB2DvsOBB2D(OBB2D* _obb1, OBB2D* _obb2);
	bool OBB2DvsSPHERE2D(OBB2D* _obb, SPHERE2D* _sphere);
	bool SPHERE2DvsSPHERE2D(SPHERE2D* _sphere1, SPHERE2D* _sphere2) const;
private:
	std::list<Colider*> colList;
};