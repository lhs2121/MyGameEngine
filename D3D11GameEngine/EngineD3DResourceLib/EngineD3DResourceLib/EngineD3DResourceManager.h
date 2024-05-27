#pragma once
#include "IEngineD3DResource.h"

class EngineD3DResourceManager : public IEngineD3DResourceManager
{
public:
	IEngineDevice* CreateDevice() override;
	IEngineVertexBuffer* CreateVertexBuffer(const char* _Name) override;
	IEngineIndexBuffer* CreateIndexBuffer(const char* _Name) override;
	IEngineInputLayout* CreateInputLayout(const char* _Name) override;
	IEngineVertexShader* CreateVertexShader(const char* _Name) override;
	IEnginePixelShader* CreatePixelShader(const char* _Name) override;
	IEngineRasterizer* CreateRasterizer(const char* _Name) override;
	IEngineDepthStencil* CreateDepthStencil(const char* _Name) override;
	IEngineTexture* CreateTexture(const char* _Name) override;

	IEngineVertexBuffer* FindVertexBuffer(const char* _Name) override;
	IEngineIndexBuffer* FindIndexBuffer(const char* _Name) override;
	IEngineInputLayout* FindInputLayout(const char* _Name) override;
	IEngineVertexShader* FindVertexShader(const char* _Name) override;
	IEngineRasterizer* FindRasterizer(const char* _Name) override;
	IEnginePixelShader* FindPixelShader(const char* _Name) override;
	IEngineDepthStencil* FindDepthStencil(const char* _Name) override;
	IEngineTexture* FindTexture(const char* _Name) override;

	void Release() override;
private:
	EngineDevice* Device = nullptr;
	std::map<EngineString, IEngineVertexBuffer*> VBMap;
	std::map<EngineString, IEngineIndexBuffer*> IBMap;
	std::map<EngineString, IEngineInputLayout*> IAMap;
	std::map<EngineString, IEngineVertexShader*> VSMap;
	std::map<EngineString, IEnginePixelShader*> PSMap;
	std::map<EngineString, IEngineRasterizer*> RSMap;
	std::map<EngineString, IEngineDepthStencil*> DSMap;

	std::map<EngineString, IEngineTexture*> TexMap;
};