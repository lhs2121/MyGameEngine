#pragma once
#include <ResourceLib\ResourceAPI.h>
#include "Object.h"


class Camera;
class  Renderer : public Object
{
public:
	~Renderer();

	void Awake() override;
	void Update(float _deltaTime) override;
	void Release() override;
	virtual void Render();

	void SetMesh(const char* _name);
	void SetMaterial(const char* _name);

	template<typename T>
	void SetRenderOrder(T _order);
	void SetRenderOrder(int _order);

	Mesh* GetMesh() { return pMesh; }
	Material* GetMaterial() { return pMaterial; }
	float4 GetImagerScale() const { return imageScale; }
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

template<typename T>
inline void Renderer::SetRenderOrder(T _order)
{
	SetRenderOrder((int)_order);
}
