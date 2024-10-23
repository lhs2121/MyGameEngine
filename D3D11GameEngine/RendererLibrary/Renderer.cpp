#include "pch.h"
#include "Renderer.h"


CRenderer::~CRenderer()
{
	m_pDeviceContext->Release();
	m_pSwapChain->Release();
	m_pRenderTargetBuffer->Release();
	m_pDepthStencilBuffer->Release();
	m_pDepthStencilView->Release();
	m_pRenderTargetView->Release();
	m_pBasicInputLayout->Release();
	delete m_pConstantBuffer_transform;
	delete m_pConstantBuffer_color;

	for (auto& pair : m_mapMesh)
	{
		CMesh* mesh = pair.second;
		delete mesh;
	}
	for (auto& pair : m_mapMaterial)
	{
		CMaterial* material = pair.second;
		delete material;
	}
	for (auto& pair : m_mapTexture)
	{
		ID3D11ShaderResourceView* srv = pair.second;
		srv->Release();
	}
	for (auto& pair : m_mapSpriteObject)
	{
		CSpriteObject* obj = pair.second;
		delete obj;
	}

//#if defined(DEBUG) || defined(_DEBUG)
//	ID3D11Debug* dxgiDebug;
//
//	if (S_OK == m_pDevice->QueryInterface(IID_PPV_ARGS(&dxgiDebug)))
//	{
//		dxgiDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
//		dxgiDebug = nullptr;
//	}
//#endif
	m_pDevice->Release();
}

void CRenderer::Initalize(UINT winSizeX, UINT winSizeY, HWND& hwnd)
{
	IDXGIFactory* pFact = nullptr;
	IDXGIAdapter* pAdap = nullptr;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFact));
	pFact->EnumAdapters(0, &pAdap);

	HRESULT rs = D3D11CreateDevice(pAdap, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, nullptr,
		D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pDeviceContext);
	if (rs != S_OK)
		__debugbreak();

	DXGI_SWAP_CHAIN_DESC scDesc = { 0 };
	scDesc.BufferDesc.Width = winSizeX;
	scDesc.BufferDesc.Height = winSizeY;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	scDesc.BufferCount = 2;
	scDesc.OutputWindow = hwnd;
	scDesc.Windowed = true;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (S_OK != pFact->CreateSwapChain(m_pDevice, &scDesc, &m_pSwapChain))
		__debugbreak();

	if (S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pRenderTargetBuffer)))
		__debugbreak();

	if (S_OK != m_pDevice->CreateRenderTargetView(m_pRenderTargetBuffer, nullptr, &m_pRenderTargetView))
		__debugbreak();

	D3D11_TEXTURE2D_DESC dsbDesc;
	dsbDesc.Width = winSizeX;
	dsbDesc.Height = winSizeY;
	dsbDesc.MipLevels = 1;
	dsbDesc.ArraySize = 1;
	dsbDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsbDesc.SampleDesc.Count = 1;
	dsbDesc.SampleDesc.Quality = 0;
	dsbDesc.Usage = D3D11_USAGE_DEFAULT;
	dsbDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsbDesc.CPUAccessFlags = 0;
	dsbDesc.MiscFlags = 0;

	if (S_OK != m_pDevice->CreateTexture2D(&dsbDesc, nullptr, &m_pDepthStencilBuffer))
		__debugbreak();

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = dsbDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	if (S_OK != m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &dsvDesc, &m_pDepthStencilView))
		__debugbreak();

	D3D11_VIEWPORT vpDesc;
	vpDesc.Width = (FLOAT)winSizeX;
	vpDesc.Height = (FLOAT)winSizeY;
	vpDesc.MinDepth = 0;
	vpDesc.MaxDepth = 1;
	vpDesc.TopLeftX = 0;
	vpDesc.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vpDesc);

	pFact->Release();
	pAdap->Release();

	m_matView = XMMatrixLookToLH(m_CameraPosition, m_CameraEyeDirection, m_CameraUpDirection);
	m_matProjection = XMMatrixPerspectiveFovLH(m_degFovY * Deg2Rad, (float)winSizeX / (float)winSizeY, m_near, m_far);

	CreateBasicMesh();
	CreateBasicMaterial();

	m_pConstantBuffer_transform = CreateConstantBuffer("DebugTransform", &m_matWorld, sizeof(XMMATRIX) * 3, "vs", 0);
	m_pConstantBuffer_color = CreateConstantBuffer("DebugColor", &m_color, sizeof(XMVECTOR), "ps", 1);

	D3D11_INPUT_ELEMENT_DESC iaDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,16,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	if (S_OK != m_pDevice->CreateInputLayout(iaDesc, 3, m_pBasicSprite2D->m_pCompiledVertexShader->GetBufferPointer(),
		m_pBasicSprite2D->m_pCompiledVertexShader->GetBufferSize(), &m_pBasicInputLayout))
		__debugbreak();
}

void CRenderer::StartRender()
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
}

void CRenderer::EndRender()
{
	m_pSwapChain->Present(0, 0);
}

void CRenderer::DrawRect(const XMMATRIX& matWorld, const XMVECTOR& color)
{
	m_matWorld = matWorld;
	m_color = color;

	m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDeviceContext->IASetInputLayout(m_pBasicInputLayout);

	m_pRect2D->Draw(m_pDeviceContext);
	m_pBasicColor->Draw(m_pDeviceContext);
	m_pConstantBuffer_transform->Draw(m_pDeviceContext);
	m_pConstantBuffer_color->Draw(m_pDeviceContext);
	m_pDeviceContext->DrawIndexed(6, 0, 0);
}

void CRenderer::DrawSprite(const XMMATRIX& matWorld, ISpriteObject* pSpriteObject)
{
	m_matWorld = matWorld;
	m_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDeviceContext->IASetInputLayout(m_pBasicInputLayout);
	((CSpriteObject*)pSpriteObject)->Draw(m_pDeviceContext);
	m_pDeviceContext->DrawIndexed(6, 0, 0);
}

void CRenderer::SetTexture(const WCHAR* wszFile, IMaterial* pMaterial)
{
	if (m_mapTexture.find(wszFile) == m_mapTexture.end())
		__debugbreak();

	((CMaterial*)pMaterial)->m_pShaderResourceView = m_mapTexture[wszFile];
}

ISpriteObject* CRenderer::CreateSpriteObject(const char* name)
{
	CSpriteObject* pSpriteObject = new CSpriteObject;
	pSpriteObject->m_pRenderer = this;
	pSpriteObject->m_pConstantBuffer_transform = CreateConstantBuffer("a", &m_matWorld, sizeof(XMMATRIX) * 3, "vs", 0);
	pSpriteObject->m_pConstantBuffer_spriteData = CreateConstantBuffer("b", &pSpriteObject->m_curSpriteData, sizeof(SpriteData), "ps", 1);
	pSpriteObject->m_pMaterial = m_mapMaterial["BasicSprite2D"]->Copy();
	pSpriteObject->m_pMesh = m_mapMesh["Rect2D"];

	m_mapSpriteObject.insert({ name,pSpriteObject });
	return pSpriteObject;
}

void CRenderer::LoadTexture(const WCHAR* wszFilePath)
{
	WCHAR* wszFullPath = new WCHAR[256];
	GetCurrentDirectoryW(256, wszFullPath);
	PathAppendW(wszFullPath, wszFilePath);

	WCHAR* wszFileName = PathFindFileNameW(wszFilePath);
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

	if (S_OK != DirectX::CreateShaderResourceView(m_pDevice, scratchImage.GetImages(),scratchImage.GetImageCount(), metaData, &pSRV))
		__debugbreak();

	m_mapTexture.insert({ wszFileName,pSRV });

	delete[] wszFullPath;
}

void CRenderer::LoadShader(const WCHAR* wszShaderPath)
{
	WCHAR* wszCurrentDir = new WCHAR[256];
	GetCurrentDirectoryW(256, wszCurrentDir);
	PathAppendW(wszCurrentDir, wszShaderPath);

	WCHAR* wszFileName = PathFindFileNameW(wszShaderPath);
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
	if (S_OK != m_pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, &pVertexShader))
		__debugbreak();

	szMainName[len + 1] = 'P';
	if (S_OK != D3DCompileFromFile(wszCurrentDir, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, szMainName, "ps_5_0", flag, 0, &pPixelShaderBlob, &pErrorBlob))
	{
		char* error = static_cast<char*>(pErrorBlob->GetBufferPointer());
		__debugbreak();
	}
	if (S_OK != m_pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, &pPixelShader))
		__debugbreak();

	m_mapShader.insert({ wszFileName, std::make_pair(pVertexShader, pPixelShader) });

	delete[] szMainName;
	delete[] szFileName;
	delete[] wszCurrentDir;
}

CMesh* CRenderer::CreateMesh(const char* meshName, void* pVertexList, UINT vertexSize, UINT vertexStride, void* pIndexList, UINT indexSize, USHORT indexStride)
{
	CMesh* pMesh = new CMesh;
	pMesh->m_vertexStrides = vertexStride;
	pMesh->m_indexStrides = indexStride;

	D3D11_BUFFER_DESC vbDesc = { vertexSize, D3D11_USAGE_DEFAULT,D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vbData = { pVertexList, 0, 0 };

	D3D11_BUFFER_DESC ibDesc = { indexSize, D3D11_USAGE_DEFAULT,D3D10_BIND_INDEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA ibData = { pIndexList, 0, 0 };

	if (S_OK != m_pDevice->CreateBuffer(&vbDesc, &vbData, &pMesh->m_pVertexBuffer))
		__debugbreak();

	if (S_OK != m_pDevice->CreateBuffer(&ibDesc, &ibData, &pMesh->m_pIndexBuffer))
		__debugbreak();

	m_mapMesh.insert({ meshName,pMesh });
	return pMesh;
}

CMaterial* CRenderer::CreateMaterial(const char* materialName, const WCHAR* wszShaderPath, const WCHAR* wszTexFileName, D3D11_RASTERIZER_DESC* pRsDesc,
	D3D11_SAMPLER_DESC* pSamplerDesc, D3D11_BLEND_DESC* pBlendDesc, D3D11_DEPTH_STENCIL_DESC* pDsDesc)
{
	CMaterial* pMaterial = new CMaterial;

	if (wszTexFileName)
	{
		if (m_mapTexture.find(wszTexFileName) == m_mapTexture.end())
			__debugbreak();
		pMaterial->m_pShaderResourceView = m_mapTexture[wszTexFileName];
	}
	if (pRsDesc)
	{
		if (S_OK != m_pDevice->CreateRasterizerState(pRsDesc, &pMaterial->m_pRasterizerState))
			__debugbreak();
	}
	if (pSamplerDesc)
	{
		if (S_OK != m_pDevice->CreateSamplerState(pSamplerDesc, &pMaterial->m_pSamplerState))
			__debugbreak();
	}
	if (pBlendDesc)
	{
		if (S_OK != m_pDevice->CreateBlendState(pBlendDesc, &pMaterial->m_pBlendState))
			__debugbreak();
	}
	if (pDsDesc)
	{
		if (S_OK != m_pDevice->CreateDepthStencilState(pDsDesc, &pMaterial->m_pDepthStencilState))
			__debugbreak();
	}

	m_mapMaterial.insert({ materialName,pMaterial });
	return pMaterial;
}

CConstantBuffer* CRenderer::CreateConstantBuffer(const char* bufferName, void* pData, UINT dataSize, const char* szTargerShader, int slotNum)
{
	CConstantBuffer* pConstantBuffer = new CConstantBuffer();
	pConstantBuffer->m_pData = pData;
	pConstantBuffer->m_dataSize = dataSize;
	pConstantBuffer->m_slot = slotNum;
	pConstantBuffer->m_szTargetShader = szTargerShader;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = dataSize;
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA cbData;
	cbData.pSysMem = pData;
	cbData.SysMemPitch = 0;
	cbData.SysMemSlicePitch = 0;

	if (S_OK != m_pDevice->CreateBuffer(&cbDesc, &cbData, &pConstantBuffer->m_pBuffer))
		__debugbreak();

	return pConstantBuffer;
}