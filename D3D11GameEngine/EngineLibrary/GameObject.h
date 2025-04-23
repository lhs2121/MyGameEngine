#pragma once
#include <DirectXMath.h>
#include <list>

using namespace DirectX;
struct IRenderer;
struct IInputObject;
class GameObject
{
public:
	void TransformUpdate();
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update(float deltaTime) {}
	virtual void Release() {}

	XMVECTOR scale = { 1,1,1,1 };
	XMVECTOR rot = { 0,0,0,1 };
	XMVECTOR pos = { 0,0,0,1 };
	XMMATRIX world = XMMatrixIdentity();
	IRenderer* renderer = nullptr;
	IInputObject* inputObject = nullptr;
	const char* name;
	bool isUpdate = false;
	bool isDestroy = false;
	GameObject* parent = nullptr;
	std::list<GameObject*> childList;
};