#include "pch.h"
#include "GameObject.h"

GameObject::~GameObject()
{
	for (GameObject* obj : childList)
	{
		delete obj;
	}
}

void GameObject::TransformUpdate()
{
	XMMATRIX matLocalScale = XMMatrixScalingFromVector(scale);
	XMMATRIX matLocalRot = XMMatrixRotationRollPitchYawFromVector(rot);
	XMMATRIX matLocalPos = XMMatrixTranslationFromVector(pos);

	world = matLocalScale * matLocalRot * matLocalPos;
	if (parent)
	{
		world *= parent->world;
	}

	for (GameObject* obj : childList)
	{
		obj->TransformUpdate();
	}
}

void GameObject::SetScale(float x, float y, float z)
{
	scale.m128_f32[0] = x;
	scale.m128_f32[1] = y;
	scale.m128_f32[2] = z;

	isTransformChanged = true;
}

void GameObject::SetRot(float x, float y, float z)
{
	rot.m128_f32[0] = XMConvertToRadians(x);
	rot.m128_f32[1] = XMConvertToRadians(y);
	rot.m128_f32[2] = XMConvertToRadians(z);

	isTransformChanged = true;
}

void GameObject::SetPos(float x, float y, float z)
{
	pos.m128_f32[0] = x;
	pos.m128_f32[1] = y;
	pos.m128_f32[2] = z;

	isTransformChanged = true;
}