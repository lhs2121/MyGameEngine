#pragma once
#include "D3D11API.h"
#include "EngineInputLayout.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineDepthStencil.h"
#include "EngineSampler.h"
#include "EngineTexture.h"

class EngineMaterial : public IMaterial
{
public:
	void SetShader(const char* _ShaderName) override;
	void SetRS(const char* _RSName) override;
	void SetDS(const char* _DSName) override;
	void SetSampler(const char* _SamplerName) override;
	void SetTexture(const char* _TextureName) override;
	void IntoPipeline() override;

	void SetDevice(ID3D11Device* _DevicePtr) override { }
	void SetContext(ID3D11DeviceContext* _ContextPtr) override {}

	IEngineVertexShader* GetVS() override;

	EngineInputLayout*         pIA = nullptr;
	EngineVertexShader*        pVS = nullptr;
	EnginePixelShader*         pPS = nullptr;
	EngineRasterizer*          pRS = nullptr;
	EngineDepthStencil*        pDS = nullptr;
	EngineSampler*             pSampler = nullptr;
	EngineTexture*             pTexture = nullptr;
};