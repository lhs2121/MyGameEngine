#pragma once
#include <D3D11Lib\D3D11API.h>
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

	IMesh* GetMesh() { return pMesh; }
	IMaterial* GetMaterial() { return pMaterial; }
	float4 GetImagerScale() const { return imageScale; }

	void SetMesh(const char* _name);
	void SetMaterial(const char* _name);

	void SetRenderOrder(int _order);
	int GetRenderOrder() const { return renderOrder; }
protected:
	Camera* pCamera = nullptr;
	int renderOrder = 0;

	float4 imageScale;
	IMesh* pMesh = nullptr;
	IMaterial* pMaterial = nullptr;
	IInputLayout* pIA = nullptr;
	IConstantBuffer* pTransformBuffer = nullptr;
};


