#pragma once
#include <BaseLibrary\Interface.h>
#include <DirectXMath.h>
#include <list>
using namespace DirectX;

class Object;
class Transform
{
public:
	void SetLocalScale(CXMVECTOR _scale);
	void SetLocalRotation(CXMVECTOR _rotation);
	void SetLocalPosition(CXMVECTOR _pos);

	void AddLocalScale(CXMVECTOR _scale);
	void AddLocalRotation(CXMVECTOR _rotation);
	void AddLocalPosition(CXMVECTOR _pos);

	void SetParent(Transform* _parent);
	void TransformUpdate();


	XMVECTOR vecLocalScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR vecLocalRotation;
	XMVECTOR vecLocalPosition;
	
	XMVECTOR vecRecievedScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR vecRecievedRotation;
	XMVECTOR vecRecievedPosition;
	
	XMVECTOR vecWorldScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR vecWorldRotation;
	XMVECTOR vecWorldPosition;

	XMVECTOR quatWorld;

	XMMATRIX matWorldScale;
	XMMATRIX matWorldRotation;
	XMMATRIX matWorldPosition;

	XMMATRIX matWorld;
	XMMATRIX matView;
	XMMATRIX matProjection;
private:
	Transform* parent = nullptr;
	std::list<Transform*> childList;
};