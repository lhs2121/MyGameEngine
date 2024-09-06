#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCollision.h"
#include "EngineRenderer.h"


void EngineCollision::Awake()
{
	Name = "EngineCollision";
	GetLevel()->AddCollision(this);
	DebugRenderer = (EngineRenderer*)CreateObject(new EngineRenderer());
	DebugRenderer->SetMesh("Circle2D");
	DebugRenderer->SetMaterial("DebugLine");
	int a = 0;
}

void EngineCollision::Update(float _Delta)
{
	DebugRenderer->Transform;
	Radius = ColScale.hx();
	right = Transform.WorldPosition.x + ColScale.hx();
	left = Transform.WorldPosition.x - ColScale.hx();
	top = Transform.WorldPosition.y + ColScale.hy();
	bottom = Transform.WorldPosition.y - ColScale.hy();
}

void EngineCollision::SetColScale(float4 _Scale)
{
	ColScale = _Scale;
	DebugRenderer->Transform.SetLocalScale(ColScale);
}

bool EngineCollision::Collision(EngineCollision* _Other)
{
	if (Type == ColType::AABB2D && _Other->Type == ColType::AABB2D)
	{
		IsCollision = AABB2DAABB2D(_Other);
	}
	if (Type == ColType::Circle2D && _Other->Type == ColType::Circle2D)
	{
		IsCollision = Circle2DCircle2D(_Other);
	}
	if (Type == ColType::AABB2D && _Other->Type == ColType::Circle2D)
	{
		IsCollision = AABB2DCircle2D(_Other);
	}
	if (Type == ColType::Circle2D && _Other->Type == ColType::AABB2D)
	{
		IsCollision = _Other->AABB2DCircle2D(this);
	}
	return IsCollision;
}

bool EngineCollision::AABB2DAABB2D(EngineCollision* _Other)
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

bool EngineCollision::Circle2DCircle2D(EngineCollision* _Other)
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

bool EngineCollision::AABB2DCircle2D(EngineCollision* _Other)
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
