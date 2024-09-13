#pragma once
#include <ResourceLib\ResourceAPI.h>
#include "Object.h"
#include "Component.h"

class Camera;
class  Renderer : public Component
{
public:
	~Renderer();

	void Awake() override;
	void Update(float _deltaTime) override;

	virtual void Render();

	Mesh* GetMesh() { return pMesh; }
	Material* GetMaterial() { return pMaterial; }
	float4 GetImagerScale() const { return imageScale; }

	void SetMesh(const char* _name);
	void SetMaterial(const char* _name);

	void SetRenderOrder(int _order);
	int GetRenderOrder() const { return renderOrder; }
protected:
	Camera* pCamera = nullptr;
	int renderOrder = 0;

	float4 imageScale;
	Mesh* pMesh = nullptr;
	Material* pMaterial = nullptr;
	InputLayout* pIA = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ConstantBuffer* pTransformBuffer = nullptr;
};


