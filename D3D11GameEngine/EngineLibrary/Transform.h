#pragma once
#include <list>
#include <DirectXMath.h>
using namespace DirectX;

class Object;
class Transform
{
public:
	void SetLocalScale(CXMVECTOR vecScale);
	void SetLocalRotation(CXMVECTOR vecRotation);
	void SetLocalPosition(CXMVECTOR vecPosition);

	void AddLocalScale(CXMVECTOR vecScale);
	void AddLocalRotation(CXMVECTOR vecRotation);
	void AddLocalPosition(CXMVECTOR vecPosition);

	void SetParent(Transform* pParent);
	void TransformUpdate();


	XMVECTOR m_vecLocalScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR m_vecLocalRotation;
	XMVECTOR m_vecLocalPosition;
	
	XMVECTOR m_vecRecievedScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR m_vecRecievedRotation;
	XMVECTOR m_vecRecievedPosition;
	
	XMVECTOR m_vecWorldScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR m_vecWorldRotation;
	XMVECTOR m_vecWorldPosition;

	XMVECTOR m_quatWorld;

	XMMATRIX m_matWorldScale;
	XMMATRIX m_matWorldRotation;
	XMMATRIX m_matWorldPosition;

	XMMATRIX m_matWorld;
	XMMATRIX m_matView;
	XMMATRIX m_matProjection;
private:
	Transform* m_pParent = nullptr;
	std::list<Transform*> m_pChildTransformList;
};