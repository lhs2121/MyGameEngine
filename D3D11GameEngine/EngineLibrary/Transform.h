#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Object;
class Transform
{
public:
	void SetScale(CXMVECTOR vecScale);
	void SetRotation(CXMVECTOR vecRotation);
	void SetPosition(CXMVECTOR vecPosition);
	void AddScale(CXMVECTOR vecScale);
	void AddRotation(CXMVECTOR vecRotation);
	void AddPosition(CXMVECTOR vecPosition);

	void SetParent(Transform* pTransform);
	void TransformUpdate();

	XMVECTOR m_vecScale = { 1.0f,1.0f,1.0f,1.0f };
	XMVECTOR m_vecRot = { 0.0f,0.0f,0.0f,1.0f };
	XMVECTOR m_vecPos = { 0.0f,0.0f,0.0f,1.0f };

	XMMATRIX m_matWorld = XMMatrixIdentity();

	bool m_IsUpdate = false;
private:
	Transform* m_pParent = nullptr;
};