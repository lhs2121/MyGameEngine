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
	std::map<std::string, IEngineVertexBuffer*> VBMap;
	std::map<std::string, IEngineIndexBuffer*> IBMap;
	std::map<std::string, IEngineInputLayout*> IAMap;
	std::map<std::string, IEngineVertexShader*> VSMap;
	std::map<std::string, IEnginePixelShader*> PSMap;
	std::map<std::string, IEngineRasterizer*> RSMap;
	std::map<std::string, IEngineDepthStencil*> DSMap;

	std::map<std::string, IEngineTexture*> TexMap;
};