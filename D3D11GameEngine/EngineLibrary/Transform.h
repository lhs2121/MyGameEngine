#pragma once
#include <DirectXMath.h>
#include <initializer_list>

using namespace DirectX;

class Transform
{
public:
	void SetParent(Transform* parent) { m_pParent = parent; }

	void SetLocalPosition(std::initializer_list<float> value);
	void SetLocalScale(std::initializer_list<float> value);
	void SetLocalRotation(std::initializer_list<float> value);

	void AddLocalPosition(std::initializer_list<float> value);
	void AddLocalRotation(std::initializer_list<float> value);

	void TransformUpdate();

	XMVECTOR GetScale() const { return m_vecWorldScale; }
	XMVECTOR GetRotation() const { return m_vecWorldRotation; }
	XMVECTOR GetPosition() const { return m_vecWorldPosition; }

	XMVECTOR m_vecWorldScale = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMVECTOR m_vecWorldRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMVECTOR m_vecWorldPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMMATRIX m_matWorld = XMMatrixIdentity();

private:
	static XMVECTOR ReadVector(std::initializer_list<float> value, float zDefault, float wDefault);

	XMVECTOR m_vecLocalScale = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMVECTOR m_vecLocalRotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	XMVECTOR m_vecLocalPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
	Transform* m_pParent = nullptr;
};
