#include "Pre.h"
#include "Scene.h"
#include "Colider2D.h"
#include "Renderer.h"

void Colider2D::Awake()
{
	scene->AddCollision(this);
}

void Colider2D::Update(float _deltaTime)
{
	radius = colScale.hx();
	right = transform.worldPosition.x + colScale.hx();
	left = transform.worldPosition.x - colScale.hx();
	top = transform.worldPosition.y + colScale.hy();
	bottom = transform.worldPosition.y - colScale.hy();
}

void Colider2D::SetColScale(float4 _scale)
{
	colScale = _scale;
}

bool Colider2D::Collision(Colider2D* _Other)
{
	if (colType == ColType::AABB2D && _Other->colType == ColType::AABB2D)
	{
		isCollision = AABB2DAABB2D(_Other);
	}
	if (colType == ColType::Circle2D && _Other->colType == ColType::Circle2D)
	{
		isCollision = Circle2DCircle2D(_Other);
	}
	if (colType == ColType::AABB2D && _Other->colType == ColType::Circle2D)
	{
		isCollision = AABB2DCircle2D(_Other);
	}
	if (colType == ColType::Circle2D && _Other->colType == ColType::AABB2D)
	{
		isCollision = _Other->AABB2DCircle2D(this);
	}

	_Other->isCollision = isCollision;
	return isCollision;
}

bool Colider2D::AABB2DAABB2D(Colider2D* _other) const
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

bool Colider2D::Circle2DCircle2D(Colider2D* _other) const
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

bool Colider2D::AABB2DCircle2D(Colider2D* _other)
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
