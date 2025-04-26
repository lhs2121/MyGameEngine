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
	void SetScale(float x ,float y,float z = 1);
	void SetRot(float x, float y, float z = 0);
	void SetPos(float x, float y, float z = 0);
	virtual void Init() {};
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void End() {};
	const char* name;
	bool isUpdate = false;
	bool isDestroy = false;
	bool isTransformChanged = false;
private:
	virtual ~GameObject();
	IRenderer* renderer;
	XMVECTOR scale = { 1,1,1,1 };
	XMVECTOR rot = { 0,0,0,1 };
	XMVECTOR pos = { 0,0,0,1 };
	XMMATRIX world = XMMatrixIdentity();
	GameObject* parent = nullptr;
	std::list<GameObject*> childList;
};
