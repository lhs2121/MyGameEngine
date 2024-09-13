#pragma once
#include <BaseLib\BaseAPI.h>

class Object;
class Transform
{
public:
	void SetWorldViewProjection(float4x4& _viewMat, float4x4& _projectionMat);

	void SetLocalScale(float4 _scale);
	void SetLocalRotation(float4 _rotation);
	void SetLocalPos(float4 _pos);

	void AddLocalScale(float4 _scale);
	void AddLocalRotation(float4 _rotation);
	void AddLocalPos(float4 _pos);

	void SetScale(float4 _scale);
	void SetRotation(float4 _rotation);
	void SetPos(float4 _pos);

	void AddScale(float4 _scale);
	void AddRotation(float4 _rotation);
	void AddPos(float4 _pos);

	void SetParent(Transform* _parentTransform);

	void TransformUpdate();

	float4 localScale = { 1.0f,1.0f,1.0f,1.0f };
	float4 localRotation;
	float4 localPosition;

	float4 scale = { 1.0f,1.0f,1.0f,1.0f };
	float4 rotation;
	float4 position;

	float4 worldScale = { 1.0f,1.0f,1.0f,1.0f };
	float4 worldRotation;
	float4 worldPosition;

	float4x4 scaleMat;
	float4x4 rotationMat;
	float4x4 positionMat;

	float4x4 worldMat;
	float4x4 viewMat;
	float4x4 projectionMat;

	float4x4 worldViewProjectionMat;

	Transform* parentTransform = nullptr;
	Object* parentObject = nullptr;
	std::list<Transform*> childTransformList;
};