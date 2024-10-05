#pragma once
#include "Colider.h"
class ColGroup
{
	friend class Scene;
public:
	void Collision(Colider* _col, ColGroup* _group);

	bool AABBvsAABB(AABB* _aabb1, AABB* _aabb2) const;
	bool AABBvsSPHERE(AABB* _aabb, SPHERE* _sphere);
	bool AABBvsOBB(AABB* _aabb, OBB* _obb);

	bool OBBvsOBB(OBB* _obb1, OBB* _obb2);
	bool OBBvsSPHERE(OBB* _obb, SPHERE* _sphere);
	bool SPHEREvsSPHERE(SPHERE* _sphere1, SPHERE* _sphere2) const;
private:
	std::list<Colider*> colList;
};