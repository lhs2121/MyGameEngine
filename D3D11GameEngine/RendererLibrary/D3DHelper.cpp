#include "pch.h"
#include "D3DHelper.h"

ID3D11Buffer* D3DHelper::CreateVertexBuffer(ID3D11Device* pDevice, void* pList, UINT size, UINT stride)
{
	ID3D11Buffer* pResult;
	D3D11_BUFFER_DESC vbDesc = { size, D3D11_USAGE_DEFAULT,D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vbData = { pList, 0, 0 };

	if (S_OK != pDevice->CreateBuffer(&vbDesc, &vbData, &pResult))
		__debugbreak();

	return pResult;
}

ID3D11Buffer* D3DHelper::CreateIndexBuffer(ID3D11Device* pDevice, void* pList, UINT size, UINT stride)
{
	ID3D11Buffer* pResult;
	D3D11_BUFFER_DESC ibDesc = { size, D3D11_USAGE_DEFAULT,D3D10_BIND_INDEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA ibData = { pList, 0, 0 };

	if (S_OK != pDevice->CreateBuffer(&ibDesc, &ibData, &pResult))
		__debugbreak();

	return pResult;
}

ConstantBuffer* D3DHelper::CreateConstantBuffer(ID3D11Device* pDevice, void* pData, UINT size, int slot, const char* szShaderType)
{
	ConstantBuffer* pResult = new ConstantBuffer;

	ID3D11Buffer* pBuffer;

	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subData;
	subData.pSysMem = pData;
	subData.SysMemPitch = 0;
	subData.SysMemSlicePitch = 0;

	if (S_OK != pDevice->CreateBuffer(&desc, &subData, &pBuffer))
		__debugbreak();

	pResult->m_szShaderType = szShaderType;
	pResult->m_slot = slot;
	pResult->m_pData = pData;
	pResult->m_pBuffer = pBuffer;
	pResult->m_dataSize = size;
	return pResult;
}

void D3DHelper::Initialize(ID3D11Device* pDevice)
{
	SimpleVertex Rect2D[] =
	{
		{ float4(-0.5f, 0.5f, 0.0f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f, 0.5f, 0.0f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(0.5f,-0.5f, 0.0f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f,-0.5f, 0.0f, 1.0f), float2(0.0f, 1.0f) }
	};

	USHORT Rect2DIndex[]
	{
		0,1,2,
		0,2,3
	};

	pRect2D = CreateVertexBuffer(pDevice, Rect2D, sizeof(Rect2D), sizeof(SimpleVertex));
	pRect2DIndex = CreateIndexBuffer(pDevice, Rect2DIndex, sizeof(Rect2DIndex), sizeof(USHORT));

	SimpleVertex Rect3D[] =
	{
		// front                     
		{ float4(-0.5f,  0.5f, -0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f,  0.5f, -0.5f, 1.0f),  float2(1.0f, 0.0f) },
		{ float4(0.5f, -0.5f, -0.5f, 1.0f),  float2(1.0f, 1.0f) },
		{ float4(-0.5f, -0.5f, -0.5f, 1.0f), float2(0.0f, 1.0f) },
		// back                
		{ float4(-0.5f, -0.5f,  0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f, -0.5f,  0.5f, 1.0f),  float2(1.0f, 0.0f) },
		{ float4(0.5f,  0.5f,  0.5f, 1.0f),  float2(1.0f, 1.0f) },
		{ float4(-0.5f,  0.5f,  0.5f, 1.0f), float2(0.0f, 1.0f) },
		// left                           
		{ float4(-0.5f,  0.5f,  0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(-0.5f,  0.5f, -0.5f, 1.0f), float2(1.0f, 0.0f) },
		{ float4(-0.5f, -0.5f, -0.5f, 1.0f), float2(1.0f, 1.0f) },
		{ float4(-0.5f, -0.5f,  0.5f, 1.0f), float2(0.0f, 1.0f) },
		// right                          
		{ float4(0.5f,  0.5f, -0.5f, 1.0f),  float2(0.0f, 0.0f) },
		{ float4(0.5f,  0.5f,  0.5f, 1.0f),  float2(1.0f, 0.0f) },
		{ float4(0.5f, -0.5f,  0.5f, 1.0f),  float2(1.0f, 1.0f) },
		{ float4(0.5f, -0.5f, -0.5f, 1.0f),  float2(0.0f, 1.0f) },
		// top                            
		{ float4(-0.5f,  0.5f,  0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f,  0.5f,  0.5f, 1.0f),  float2(1.0f, 0.0f) },
		{ float4(0.5f,  0.5f, -0.5f, 1.0f),  float2(1.0f, 1.0f) },
		{ float4(-0.5f,  0.5f, -0.5f, 1.0f), float2(0.0f, 1.0f) },
		// bottom                         
		{ float4(-0.5f, -0.5f, -0.5f, 1.0f), float2(0.0f, 0.0f) },
		{ float4(0.5f, -0.5f, -0.5f, 1.0f),  float2(1.0f, 0.0f) },
		{ float4(0.5f, -0.5f,  0.5f, 1.0f),  float2(1.0f, 1.0f) },
		{ float4(-0.5f, -0.5f,  0.5f, 1.0f), float2(0.0f, 1.0f) }
	};

	USHORT Rect3DIndex[]
	{
		// front
		0,1,2,
		2,3,0,
		// back
		4,5,6,
		6,7,4,
		// left
		8,9,10,
		10,11,8,
		// right
		12,13,14,
		14,15,12,
		// top
		16,17,18,
		18,19,16,
		// bottom
		20,21,22,
		22,23,20
	};


	pRect3D = CreateVertexBuffer(pDevice, Rect3D, sizeof(Rect3D), sizeof(SimpleVertex));
	pRect3DIndex = CreateIndexBuffer(pDevice, Rect3DIndex, sizeof(Rect3DIndex), sizeof(USHORT));

	{
		D3D11_RASTERIZER_DESC desc = {};
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		desc.FrontCounterClockwise = false; //시계방향
		desc.DepthBias = 0;
		desc.DepthBiasClamp = 0;
		desc.SlopeScaledDepthBias = 0;
		desc.DepthClipEnable = true;
		desc.ScissorEnable = false;
		desc.MultisampleEnable = true;
		desc.AntialiasedLineEnable = false;

		if (S_OK != pDevice->CreateRasterizerState(&desc, &pSolid))
			__debugbreak();
	}

	{
		D3D11_RASTERIZER_DESC desc = {};
		desc.FillMode = D3D11_FILL_WIREFRAME;
		desc.CullMode = D3D11_CULL_NONE;
		desc.FrontCounterClockwise = false;
		desc.DepthBias = 0;
		desc.DepthBiasClamp = 0;
		desc.SlopeScaledDepthBias = 0;
		desc.DepthClipEnable = true;
		desc.ScissorEnable = false;
		desc.MultisampleEnable = false;
		desc.AntialiasedLineEnable = false;

		if (S_OK != pDevice->CreateRasterizerState(&desc, &pWireFrame))
			__debugbreak();
	}

	{
		D3D11_SAMPLER_DESC desc = {};
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.MipLODBias = 0.0f;
		desc.MaxAnisotropy = 1;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;
		desc.MinLOD = 0;
		desc.MaxLOD = D3D11_FLOAT32_MAX;

		if (S_OK != pDevice->CreateSamplerState(&desc, &pPoint))
			__debugbreak();
	}

	{
		D3D11_BLEND_DESC desc = { 0 };
		desc.AlphaToCoverageEnable = true;
		desc.IndependentBlendEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		if (S_OK != pDevice->CreateBlendState(&desc, &pAlpha))
			__debugbreak();
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc = { 0 };
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		desc.StencilEnable = false;

		if (S_OK != pDevice->CreateDepthStencilState(&desc, &pDepthEnabledState))
			__debugbreak();
	}

	LoadShader(pDevice, L"Assets\\Shaders\\BasicColorShader.hlsl");
	LoadShader(pDevice, L"Assets\\Shaders\\BasicSprite2DShader.hlsl");
	LoadTexture(pDevice, L"Assets\\Texture\\asdf.jpg");

	D3D11_INPUT_ELEMENT_DESC iaDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,16,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	ShaderData* pData = pShaders[L"BasicSprite2DShader.hlsl"];

	ID3DBlob* pCompiledVertexShader = pData->m_pCompiledVertexShader;
	if (S_OK != pDevice->CreateInputLayout(iaDesc, 3, pCompiledVertexShader->GetBufferPointer(), pCompiledVertexShader->GetBufferSize(), &pLayout))
		__debugbreak();
}

void D3DHelper::LoadTexture(ID3D11Device* pDevice, const WCHAR* wszTexFile)
{
	WCHAR* wszFullPath = new WCHAR[256];
	GetCurrentDirectoryW(256, wszFullPath);
	PathAppendW(wszFullPath, wszTexFile);

	WCHAR* wszFileName = PathFindFileNameW(wszTexFile);
	WCHAR* wszExt = PathFindExtensionW(wszFileName);

	ID3D11ShaderResourceView* pSRV = nullptr;
	TexMetadata metaData;
	ScratchImage scratchImage;

	if (wcscmp(wszExt, L".dds") == 0)
	{
		if (S_OK != DirectX::LoadFromDDSFile(wszFullPath, DirectX::DDS_FLAGS_NONE, &metaData, scratchImage))
			__debugbreak();
	}
	else if (wcscmp(wszExt, L".png") == 0 || wcscmp(wszExt, L".jpg") == 0 || wcscmp(wszExt, L".jpeg") == 0 || wcscmp(wszExt, L".gif") == 0 || wcscmp(wszExt, L".bmp") == 0)
	{
		if (S_OK != DirectX::LoadFromWICFile(wszFullPath, DirectX::WIC_FLAGS_NONE, &metaData, scratchImage))
			__debugbreak();
	}
	else if (wcscmp(wszExt, L".tga") == 0)
	{
		if (S_OK != DirectX::LoadFromTGAFile(wszFullPath, &metaData, scratchImage))
			__debugbreak();
	}

	if (S_OK != DirectX::CreateShaderResourceView(pDevice, scratchImage.GetImages(), scratchImage.GetImageCount(), metaData, &pSRV))
		__debugbreak();

	pTextures.insert({ wszFileName,pSRV });

	delete[] wszFullPath;
}

void D3DHelper::LoadShader(ID3D11Device* pDevice, const WCHAR* wszShaderFile)
{
	WCHAR* wszCurrentDir = new WCHAR[256];
	GetCurrentDirectoryW(256, wszCurrentDir);
	PathAppendW(wszCurrentDir, wszShaderFile);

	WCHAR* wszFileName = PathFindFileNameW(wszShaderFile);
	char* szFileName = new char[256];
	WideCharToMultiByte(CP_UTF8, 0, wszFileName, -1, szFileName, 256, NULL, NULL);

	char* szMainName = new char[256];
	int len = 0;
	char* pExtention = szFileName;
	while (*pExtention != '.')
	{
		len++;
		pExtention++;
	}
	memcpy_s(szMainName, len, szFileName, len);
	szMainName[len] = '_';
	szMainName[len + 1] = 'V';
	szMainName[len + 2] = 'S';
	szMainName[len + 3] = '\0';

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3DBlob* pVertexShaderBlob = nullptr;
	ID3DBlob* pPixelShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;

	int flag;
#ifdef _DEBUG
	flag = D3DCOMPILE_DEBUG;
#endif
	flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;


	if (S_OK != D3DCompileFromFile(wszCurrentDir, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, szMainName, "vs_5_0", flag, 0, &pVertexShaderBlob, &pErrorBlob))
	{
		char* error = static_cast<char*>(pErrorBlob->GetBufferPointer());
		__debugbreak();
	}
	if (S_OK != pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, &pVertexShader))
		__debugbreak();

	szMainName[len + 1] = 'P';
	if (S_OK != D3DCompileFromFile(wszCurrentDir, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, szMainName, "ps_5_0", flag, 0, &pPixelShaderBlob, &pErrorBlob))
	{
		char* error = static_cast<char*>(pErrorBlob->GetBufferPointer());
		__debugbreak();
	}
	if (S_OK != pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, &pPixelShader))
		__debugbreak();

	ShaderData* data = new ShaderData;
	data->m_pVertexShader = pVertexShader;
	data->m_pPixelShader = pPixelShader;
	data->m_pCompiledVertexShader = pVertexShaderBlob;

	pShaders.insert({ wszFileName, data });

	pPixelShaderBlob->Release();
	delete[] szMainName;
	delete[] szFileName;
	delete[] wszCurrentDir;
}
