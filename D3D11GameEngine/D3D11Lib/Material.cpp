#include "Pre.h"
#include "Material.h"
#include "ResManager.h"

void Material::IntoPipeline()
{
	pVS->IntoPipeline(ContextPtr);
	pPS->IntoPipeline(ContextPtr);
	pRS->IntoPipeline(ContextPtr);
	pDS->IntoPipeline(ContextPtr);
	pSampler->IntoPipeline(ContextPtr, ShaderType::PS, 0);
	pTexture->IntoPipeline(ContextPtr, ShaderType::PS, 0);
}

void Material::SetShader(const char* _ShaderName)
{
	pVS = (VertexShader*)ManagerPtr->Find(ResType::VS, _ShaderName);
	pPS = (PixelShader*)ManagerPtr->Find(ResType::PS, _ShaderName);
}

void Material::SetRS(const char* _RSName)
{
	pRS = (Rasterizer*)ManagerPtr->Find(ResType::RS, _RSName);
}

void Material::SetDS(const char* _DSName)
{
	pDS = (DepthStencil*)ManagerPtr->Find(ResType::DS, _DSName);
}

void Material::SetSampler(const char* _SamplerName)
{
	pSampler = (Sampler*)ManagerPtr->Find(ResType::Sampler, _SamplerName);
}

void Material::SetTexture(const char* _TextureName)
{
	pTexture = (Texture*)ManagerPtr->Find(ResType::Texture, _TextureName);
}

IVertexShader* Material::GetVS()
{
	return pVS;
}
