#include "Pre.h"
#include "Scene.h"

void Scene::UseQuadTree()
{
	CreateQuadTree(&pQuad);
	pQuad->Initialize(0, 0, 1366, 789, 3);
}

void Scene::CheckDeath()
{
	for (Object* object: deathNote)
	{
		object->GetParent()->RemoveChild(object);
		object->AllRelease();
		delete object;
	}
	deathNote.clear();
}



