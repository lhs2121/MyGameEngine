#include "Pre.h"
#include "EngineMaterial.h"
#include "EngineD3DManager.h"

void EngineMaterial::Setting(const char* _ShaderName)
{
	pVS = (EngineVertexShader*)EngineD3DManager::MainManager->Find(ResType::VS, _ShaderName);
	pPS = (EnginePixelShader*)EngineD3DManager::MainManager->Find(ResType::PS, _ShaderName);
	pRS = (EngineRasterizer*)EngineD3DManager::MainManager->Find(ResType::RS, "Default");
	pDS = (EngineDepthStencil*)EngineD3DManager::MainManager->Find(ResType::DS, "Default");
	pSampler = (EngineSampler*)EngineD3DManager::MainManager->Find(ResType::Sampler, "Default");
	pTexture = (EngineTexture*)EngineD3DManager::MainManager->Find(ResType::Texture, "Default");
}

void EngineMaterial::IntoPipeline()
{
	pVS->IntoPipeline();
	pPS->IntoPipeline();
	pRS->IntoPipeline();
	pDS->IntoPipeline();
}

void EngineMaterial::SetSampler(const char* _SamplerName)
{
	pSampler = (EngineSampler*)EngineD3DManager::MainManager->Find(ResType::Sampler, _SamplerName);
	pSampler->IntoPipeline(ShaderType::PS,0);
}

void EngineMaterial::SetTexture(const char* _TextureName)
{
	pTexture = (EngineTexture*)EngineD3DManager::MainManager->Find(ResType::Texture, _TextureName);
	pTexture->IntoPipeline(ShaderType::PS, 0);
}

IEngineVertexShader* EngineMaterial::GetVS()
{
	return pVS;
}
