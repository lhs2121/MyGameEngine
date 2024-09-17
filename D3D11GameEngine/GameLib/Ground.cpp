#include "Pre.h"
#include "Ground.h"

void Ground::Awake()
{	
	pColider2D = CreateChild<Colider2D>();
	pColider2D->SetColType(ColType::AABB2D);
	pColider2D->transform.SetLocalPos({ 0,-150 });
	transform.SetLocalScale({ 700,128 });
}

void Ground::Update(float _deltaTime)
{


}
