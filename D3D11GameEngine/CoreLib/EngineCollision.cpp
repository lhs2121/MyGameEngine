#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCollision.h"

void EngineCollision::Awake()
{
	GetLevel()->AddCollision(this);
}

void EngineCollision::Update(float _Delta)
{
	Radius = ColScale.hx();
	float4 WorldPos = Transform.Position + Transform.LocalPosition;
	right = WorldPos.x + ColScale.hx();
	left = WorldPos.x - ColScale.hx();
	top = WorldPos.y + ColScale.hy();
	bottom = WorldPos.y - ColScale.hy();
}

bool EngineCollision::Collision(EngineCollision* _Other)
{
	if (Type == ColType::Rect && _Other->Type == ColType::Rect)
	{
		AABB(_Other);
	}
	if (Type == ColType::Circle && _Other->Type == ColType::Circle)
	{
		Circle(_Other);
	}
	return false;
}

bool EngineCollision::AABB(EngineCollision* _Other)
{ 
	if (_Other->right < this->left)
	{
		IsCollision = false;
		return false;
	}
	if (_Other->left > this->right)
	{
		IsCollision = false;
		return false;
	}

	//여기까지 왔으면 x축은 충돌했다

	if (_Other->top < this->bottom)
	{
		IsCollision = false;
		return false;
	}
	if (_Other->bottom > this->top)
	{
		IsCollision = false;
		return false;
	}

	IsCollision = true;
	return true;
}

bool EngineCollision::Circle(EngineCollision* _Other)
{
	float Sum = _Other->Radius + Radius;
	float4 Pos1 = _Other->Transform.Position + _Other->Transform.LocalPosition;
	float4 Pos2 = Transform.Position + Transform.LocalPosition;
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
