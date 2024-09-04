#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCollision.h"
#include "EngineRenderer.h"


void EngineCollision::Awake()
{
	GetLevel()->AddCollision(this);
	DebugRenderer = (EngineRenderer*)CreateObject(new EngineRenderer());
	DebugRenderer->SetMesh("Circle2D");
	DebugRenderer->SetMaterial("DebugLine");
	DebugRenderer->Transform.SetLocalScale({ 100,100 });
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
		IsCollision = AABB(_Other);
	}
	if (Type == ColType::Circle && _Other->Type == ColType::Circle)
	{
		IsCollision = Circle(_Other);
	}
	if (Type == ColType::Rect && _Other->Type == ColType::Circle)
	{
		IsCollision = AABBvsCircle(_Other);
	}
	if (Type == ColType::Circle && _Other->Type == ColType::Rect)
	{
		IsCollision = _Other->AABBvsCircle(this);
	}
	return IsCollision;
}

bool EngineCollision::AABB(EngineCollision* _Other)
{ 
	if (_Other->right < this->left)
	{
		return false;
	}
	if (_Other->left > this->right)
	{
		return false;
	}

	//여기까지 왔으면 x축은 충돌했다

	if (_Other->top < this->bottom)
	{
		return false;
	}
	if (_Other->bottom > this->top)
	{
		return false;
	}

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

bool EngineCollision::AABBvsCircle(EngineCollision* _Other)
{
	float4 CirclePos = _Other->Transform.Position + _Other->Transform.LocalPosition;
	
	float4 Near;
	Near.x = EngineMath::Clamp(CirclePos.x, right, left);
	Near.y = EngineMath::Clamp(CirclePos.y, top, bottom);

	float D = Near.Distance(CirclePos);
	
	if (D <= _Other->Radius)
	{
		return true;
	}
	return false;
}
