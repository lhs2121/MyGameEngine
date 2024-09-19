#include "Pre.h"
#include "Scene.h"
#include "Colider.h"
#include "Renderer.h"

void Colider::Awake()
{
	GetScene()->AddCollision(this);

	debugRenderer = CreateChild<Renderer>();
	debugRenderer->SetRenderOrder(-5);
	debugRenderer->SetMesh("Box2D");
	debugRenderer->SetMaterial("WireFrame");
}

void Colider::Update(float _deltaTime)
{
	radius = transform.worldScale.hx();
	right = transform.worldPosition.x + transform.worldScale.hx();
	left = transform.worldPosition.x - transform.worldScale.hx();
	top = transform.worldPosition.y + transform.worldScale.hy();
	bottom = transform.worldPosition.y - transform.worldScale.hy();
}

void Colider::Release()
{
	int a = 0;
}

void Colider::SetColType(ColType _Type)
{
	colType = _Type; 
	const char* meshName = nullptr;
	switch (colType)
	{
	case ColType::AABB2D:
		meshName = "Box2D";
		break;
	case ColType::SPHERE2D:
		meshName = "SPHERE2D";
		break;
	}
	debugRenderer->SetMesh(meshName);
}

bool Colider::Collision(Colider* _Other)
{
	if (colType == ColType::AABB2D && _Other->colType == ColType::AABB2D)
	{
		isCollision = AABB2DAABB2D(_Other);
	}
	else if (colType == ColType::SPHERE2D && _Other->colType == ColType::SPHERE2D)
	{
		isCollision = SPHERE2DSPHERE2D(_Other);
	}
	else if (colType == ColType::AABB2D && _Other->colType == ColType::SPHERE2D)
	{
		isCollision = AABB2DSPHERE2D(_Other);
	}
	else if (colType == ColType::SPHERE2D && _Other->colType == ColType::AABB2D)
	{
		isCollision = _Other->AABB2DSPHERE2D(this);
	}

	if (isCollision)
	{
		opponent = _Other;
	}
	else
	{
		opponent = nullptr;
	}

	_Other->isCollision = isCollision;
	return isCollision;
}

bool Colider::AABB2DAABB2D(Colider* _other) const
{
	if (_other->right < this->left)
	{
		return false;
	}
	if (_other->left > this->right)
	{
		return false;
	}

	//여기까지 왔으면 x축은 충돌했다

	if (_other->top < this->bottom)
	{
		return false;
	}
	if (_other->bottom > this->top)
	{
		return false;
	}
	
	return true;
}

bool Colider::SPHERE2DSPHERE2D(Colider* _other) const
{
	float Sum = _other->radius + radius;
	float4 Pos1 = _other->transform.position + _other->transform.localPosition;
	float4 Pos2 = transform.position + transform.localPosition;
	float Distance = Pos1.Distance(Pos2);
	if (Distance > Sum)
	{
		return false;
	}
	else
	{
		return true;
	}

}

bool Colider::AABB2DSPHERE2D(Colider* _other)
{
	float4 circlePos = _other->transform.position + _other->transform.localPosition;

	float4 Near;
	Near.x = EngineMath::Clamp(circlePos.x, right, left);
	Near.y = EngineMath::Clamp(circlePos.y, top, bottom);

	float distance = Near.Distance(circlePos);

	if (distance <= _other->radius)
	{
		return true;
	}
	return false;
}
