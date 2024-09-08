#include "Pre.h"
#include "Level.h"
#include "Colider2D.h"
#include "Renderer.h"


void Colider2D::Awake()
{
	Name = "Colider2D";
	GetLevel()->AddCollision(this);
	DebugRenderer = (Renderer*)CreateObject(new Renderer());
	DebugRenderer->SetMesh("Circle2D");
	DebugRenderer->SetMaterial("DebugLine");
	int a = 0;
}

void Colider2D::Update(float _Delta)
{
	DebugRenderer->Transform;
	Radius = ColScale.hx();
	right = Transform.WorldPosition.x + ColScale.hx();
	left = Transform.WorldPosition.x - ColScale.hx();
	top = Transform.WorldPosition.y + ColScale.hy();
	bottom = Transform.WorldPosition.y - ColScale.hy();
}

void Colider2D::SetColScale(float4 _Scale)
{
	ColScale = _Scale;
	DebugRenderer->Transform.SetLocalScale(ColScale);
}

bool Colider2D::Collision(Colider2D* _Other)
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

bool Colider2D::AABB2DAABB2D(Colider2D* _Other)
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

bool Colider2D::Circle2DCircle2D(Colider2D* _Other)
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

bool Colider2D::AABB2DCircle2D(Colider2D* _Other)
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
