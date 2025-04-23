#include "GameObject.h"

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
}
