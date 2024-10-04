#pragma once
#include <BaseLib\BaseAPI.h>
using namespace DirectX;

class Object;
class Transform
{
public:
	void SetWorldViewProjection(CXMMATRIX matView, CXMMATRIX matProjection);

	void SetLocalScale(CXMVECTOR _scale);
	void SetLocalRotation(CXMVECTOR _rotation);
	void SetLocalPos(CXMVECTOR _pos);

	void AddLocalScale(CXMVECTOR _scale);
	void AddLocalRotation(CXMVECTOR _rotation);
	void AddLocalPos(CXMVECTOR _pos);

	void SetParent(Transform* _parent);
	void TransformUpdate();


	XMVECTOR localScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR localRotation;
	XMVECTOR localPosition;
	
	XMVECTOR scale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR rotation;
	XMVECTOR position;

	XMVECTOR worldScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR worldRotation;
	XMVECTOR worldPosition;

	XMVECTOR worldQuaternion;

	XMMATRIX scaleMat;
	XMMATRIX rotationMat;
	XMMATRIX positionMat;

	XMMATRIX worldMat;
	XMMATRIX viewMat;
	XMMATRIX projectionMat;

	XMMATRIX worldViewProjectionMat;

private:
	Transform* parent = nullptr;
	std::list<Transform*> childList;
};