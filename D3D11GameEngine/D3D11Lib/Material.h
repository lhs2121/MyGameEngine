#pragma once
#include "D3D11API.h"
#include "InputLayout.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Rasterizer.h"
#include "DepthStencil.h"
#include "Sampler.h"
#include "Texture.h"

class Material : public IMaterial
{
public:
	void SetShader(const char* _ShaderName) override;
	void SetRS(const char* _RSName) override;
	void SetDS(const char* _DSName) override;
	void SetSampler(const char* _SamplerName) override;
	void SetTexture(const char* _TextureName) override;
	void IntoPipeline() override;
	IVertexShader* GetVS() override;

	ID3D11DeviceContext* ContextPtr = nullptr;
	IResManager*         ManagerPtr = nullptr;

	InputLayout*         pIA = nullptr;
	VertexShader*        pVS = nullptr;
	PixelShader*         pPS = nullptr;
	Rasterizer*          pRS = nullptr;
	DepthStencil*        pDS = nullptr;
	Sampler*             pSampler = nullptr;
	Texture*             pTexture = nullptr;
};