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
	virtual void Render();

	void SetMesh(const char* _name);
	void SetMaterial(const char* _name);

	template<typename T>
	void SetRenderOrder(T _order);
	void SetRenderOrder(int _order);

	void SetConstantBuffer(const char* _name, void* pData, int _dataSize, ShaderType _type, int _slot = 0);

	Mesh* GetMesh() { return pMesh; }
	Material* GetMaterial() { return pMaterial; }
	float4 GetImagerScale() const { return imageScale; }
	int GetRenderOrder() const { return renderOrder; }
protected:
	int renderOrder = 0;
	float4 imageScale;

	Camera* pCamera = nullptr;
	Mesh* pMesh = nullptr;
	Material* pMaterial = nullptr;
	InputLayout* pIA = nullptr;
	ID3D11DeviceContext* pContext = nullptr;

	std::vector<ConstantBuffer*> ConstantBuffers;
};

template<typename T>
inline void Renderer::SetRenderOrder(T _order)
{
	SetRenderOrder((int)_order);
}
