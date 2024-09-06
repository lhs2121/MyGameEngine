#pragma once
#include "EngineObject.h"
#include <D3D11Lib\D3D11API.h>

class CoreAPI EngineRenderer : public EngineObject
{
public:
	~EngineRenderer();

	void Awake() override;
	void Update(float _Delta) override;

	virtual void Render();

	IMesh* GetMesh() { return Mesh; }
	IMaterial* GetMaterial() { return Material; }
	float4 GetImagerScale() const { return ImageScale; }

	void SetMesh(const char* _Name);
	void SetMaterial(const char* _Name);
	void SetTexture(const char* _TextureName);

protected:
	float4 ImageScale;
	IMesh* Mesh = nullptr;
	IMaterial* Material = nullptr;
	IInputLayout* pIA = nullptr;
	IConstantBuffer* TransformBuffer = nullptr;
};


