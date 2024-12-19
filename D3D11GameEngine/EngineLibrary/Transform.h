#pragma once
#include <list>
#include <DirectXMath.h>
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

	void SetParent(Transform* _m_pParent);
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
	Transform* m_pParent = nullptr;
	std::list<Transform*> childList;
};