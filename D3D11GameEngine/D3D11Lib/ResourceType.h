#pragma once
#include "d3d11.h"
#include <ThirdParty/include/DirectXTex.h>

struct STexture
{
	ID3D11ShaderResourceView* pShaderResourceView;
	DirectX::ScratchImage scratchImage;
	DirectX::TexMetadata metaData;
};