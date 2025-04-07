#pragma once
#include "ConstantBuffer.h"
#include <unordered_map>
#include <string>

class D3DHelper
{
public:
	static ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pDevice, void* pList, UINT size, UINT stride);
	static ID3D11Buffer* CreateIndexBuffer(ID3D11Device* pDevice, void* pList, UINT size, UINT stride);
	static ConstantBuffer* CreateConstantBuffer(ID3D11Device* pDevice, void* pData, UINT size, int slot, const char* szShaderType);

	void Initialize(ID3D11Device* pDevice);
	void LoadTexture(ID3D11Device* pDevice, const WCHAR* wszTexFile);
	void LoadShader(ID3D11Device* pDevice, const WCHAR* wszShaderFile);

	ID3D11Buffer* pRect2D;
	ID3D11Buffer* pRect2DIndex;

	ID3D11Buffer* pRect3D;
	ID3D11Buffer* pRect3DIndex;

	ID3D11RasterizerState* pSolid;
	ID3D11RasterizerState* pWireFrame;
	ID3D11InputLayout* pLayout;
	ID3D11SamplerState* pPoint;
	ID3D11DepthStencilState* pDepthEnabledState;
	ID3D11BlendState* pAlpha;

	std::unordered_map<std::wstring, ShaderData*> pShaders;
	std::unordered_map<std::wstring, ID3D11ShaderResourceView*> pTextures;
};