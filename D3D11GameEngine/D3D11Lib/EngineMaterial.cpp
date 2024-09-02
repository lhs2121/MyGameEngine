#include "Pre.h"
#include "EngineMaterial.h"
#include "EngineD3DManager.h"

void EngineMaterial::IntoPipeline()
{
	pVS->IntoPipeline();
	pPS->IntoPipeline();
	pRS->IntoPipeline();
	pDS->IntoPipeline();
	pSampler->IntoPipeline(ShaderType::PS, 0);
	pTexture->IntoPipeline(ShaderType::PS, 0);
}

void EngineMaterial::SetShader(const char* _ShaderName)
{
	pVS = (EngineVertexShader*)EngineD3DManager::MainManager->Find(ResType::VS, _ShaderName);
	pPS = (EnginePixelShader*)EngineD3DManager::MainManager->Find(ResType::PS, _ShaderName);
}

void EngineMaterial::SetRS(const char* _RSName)
{
	pRS = (EngineRasterizer*)EngineD3DManager::MainManager->Find(ResType::RS, _RSName);
}

void EngineMaterial::SetDS(const char* _DSName)
{
	pDS = (EngineDepthStencil*)EngineD3DManager::MainManager->Find(ResType::DS, _DSName);
}

void EngineMaterial::SetSampler(const char* _SamplerName)
{
	pSampler = (EngineSampler*)EngineD3DManager::MainManager->Find(ResType::Sampler, _SamplerName);
}

void EngineMaterial::SetTexture(const char* _TextureName)
{
	pTexture = (EngineTexture*)EngineD3DManager::MainManager->Find(ResType::Texture, _TextureName);
}

IEngineVertexShader* EngineMaterial::GetVS()
{
	return pVS;
}
