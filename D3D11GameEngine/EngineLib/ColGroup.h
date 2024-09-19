#pragma once
#include "Colider.h"
class ColGroup
{
	friend class Scene;
public:
	void Collision(Colider* _col, ColGroup* _group);

	bool AABB2DvsAABB2D(Colider* _aabb1, Colider* _aabb2) const;
	bool AABB2DvsSPHERE2D(Colider* _aabb, Colider* _sphere);
	bool AABB2DvsOBB2D(Colider* _aabb, Colider* _obb);

	bool OBB2DvsOBB2D(Colider* _obb1,Colider* _obb2);
	bool OBB2DvsSPHERE2D(Colider* _obb,Colider* _sphere);
	bool SPHERE2DvsSPHERE2D(Colider* _sphere1, Colider* _sphere2) const;
private:
	std::list<Colider*> colList;
};