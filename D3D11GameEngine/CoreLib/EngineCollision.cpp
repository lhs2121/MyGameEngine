#include "Pre.h"
#include "EngineLevel.h"
#include "EngineCollision.h"

void EngineCollision::Awake()
{
	GetLevel()->AddCollision(this);
}

void EngineCollision::Update(float _Delta)
{
	float4 WorldPos = Transform.Position + Transform.LocalPosition;
	right = WorldPos.x + ColScale.hx();
	left = WorldPos.x - ColScale.hx();
	top = WorldPos.y + ColScale.hy();
	bottom = WorldPos.y - ColScale.hy();
}

bool EngineCollision::AABB(EngineCollision* _Other)
{ 
	if (_Other->right < this->left)
	{
		return 0;
	}
	if (_Other->left > this->right)
	{
		return 0;
	}

	//여기까지 왔으면 x축은 충돌했다

	if (_Other->top < this->bottom)
	{
		return 0;
	}
	if (_Other->bottom > this->top)
	{
		return 0;
	}

	return 1;
}
