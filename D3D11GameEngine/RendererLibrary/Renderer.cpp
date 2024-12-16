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
	for (auto& pair : m_mapSRV)
	{
		auto* srv = pair.second;
		srv->Release();
	}
	for (auto& pair : m_mapRasterizer)
	{
		auto* srv = pair.second;
		srv->Release();
	}
	for (auto& pair : m_mapDepthStencil)
	{
		auto* srv = pair.second;
		srv->Release();
	}
	for (auto& pair : m_mapBlend)
	{
		auto* srv = pair.second;
		srv->Release();
	}
	for (auto& pair : m_mapSampler)
	{
		auto* srv = pair.second;
		srv->Release();
	}
	for (auto& pair : m_mapShader)
	{
		ShaderData* srv = pair.second;
		srv->m_pCompiledVertexShader->Release();
		srv->m_pPixelShader->Release();
		srv->m_pVertexShader->Release();
		delete srv;
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

void CRenderer::Initialize(UINT winSizeX, UINT winSizeY, HWND& hwnd)
{
	IDXGIFactory* pFact = nullptr;
	IDXGIAdapter* pAdap = nullptr;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFact));
	pFact->EnumAdapters(0, &pAdap);

	HRESULT rs = D3D11CreateDevice(pAdap, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &m_pDevice, &featureLevel, &m_pDeviceContext);
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

	ShaderData* pData = m_mapShader[L"BasicSprite2DShader.hlsl"];
	ID3DBlob* pCompiledVertexShader = pData->m_pCompiledVertexShader;
	if (S_OK != m_pDevice->CreateInputLayout(iaDesc, 3, pCompiledVertexShader->GetBufferPointer(), pCompiledVertexShader->GetBufferSize(), &m_pBasicInputLayout))
		__debugbreak();

	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDeviceContext->IASetInputLayout(m_pBasicInputLayout);

	IDXGISurface* pDXGISurface = nullptr;
	
	if(S_OK != m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(&pDXGISurface)))
		__debugbreak();

	m_pFontManager = new CFontManager;
		m_pFontManager->Initialize(m_pDevice, pDXGISurface);
}

void CRenderer::StartRender()
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	m_pFontManager->FontRender();
}

void CRenderer::EndRender()
{
	m_pSwapChain->Present(0, 0);
}

void CRenderer::DrawRect(const XMMATRIX& matWorld, const XMVECTOR& color)
{
	m_matWorld = matWorld;
	m_color = color;

	CMesh* pCMesh = m_mapMesh["Rect2D"];
	CMaterial* pCMaterial = m_mapMaterial["BasicColor"];

	pCMesh->Draw(m_pDeviceContext);
	pCMaterial->Draw(m_pDeviceContext);
	m_pConstantBuffer_transform->Draw(m_pDeviceContext);
	m_pConstantBuffer_color->Draw(m_pDeviceContext); 
	m_pDeviceContext->DrawIndexed(6, 0, 0);
}

void CRenderer::DrawRect2(float x, float y, float width, float height, const XMVECTOR& color)
{
	XMMATRIX matScale = XMMatrixScaling(width, height, 1.0f);
	XMMATRIX matTranslate = XMMatrixTranslation(x, y, 0.0f);

	m_matWorld = matScale * matTranslate;
	m_color = color;

	CMesh* pCMesh = m_mapMesh["Rect2D"];
	CMaterial* pCMaterial = m_mapMaterial["BasicColor"];

	pCMesh->Draw(m_pDeviceContext);
	pCMaterial->Draw(m_pDeviceContext);
	m_pConstantBuffer_transform->Draw(m_pDeviceContext);
	m_pConstantBuffer_color->Draw(m_pDeviceContext);
	m_pDeviceContext->DrawIndexed(6, 0, 0);
}

void CRenderer::DrawSprite(const XMMATRIX& matWorld, ISpriteObject* pSpriteObject)
{
	m_matWorld = matWorld;
	CMesh* pCMesh = m_mapMesh["Rect2D"];
	CMaterial* pCMaterial = m_mapMaterial["BasicSprite2D"];
	CSpriteObject* pCSpriteObject = (CSpriteObject*)pSpriteObject;

	pCMaterial->m_pShaderResourceView = pCSpriteObject->m_pSRV;
	pCMesh->Draw(m_pDeviceContext);
	pCMaterial->Draw(m_pDeviceContext);
	pCSpriteObject->Draw(m_pDeviceContext);
	m_pDeviceContext->DrawIndexed(6, 0, 0);
}

ISpriteObject* CRenderer::CreateSpriteObject(const char* name, const WCHAR* wszTexfile, int countX, int countY, float interTime)
{
	CSpriteObject* pSpriteObject = new CSpriteObject;
	pSpriteObject->m_pConstantBuffer_transform = CreateConstantBuffer("a", &m_matWorld, sizeof(XMMATRIX) * 3, "vs", 0);
	pSpriteObject->m_pConstantBuffer_spriteData = CreateConstantBuffer("b", &pSpriteObject->m_curSpriteData, sizeof(SpriteData), "ps",0);
	pSpriteObject->m_pSRV = GetShaderResourceView(wszTexfile);

	pSpriteObject->CreateAnimation(countX, countY, interTime);
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

	m_mapSRV.insert({ wszFileName,pSRV });

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

	ShaderData* data = new ShaderData;
	data->m_pVertexShader = pVertexShader;
	data->m_pPixelShader = pPixelShader;
	data->m_pCompiledVertexShader = pVertexShaderBlob;

;	m_mapShader.insert({ wszFileName, data });

    pPixelShaderBlob->Release();
	delete[] szMainName;
	delete[] szFileName;
	delete[] wszCurrentDir;
}

IMesh* CRenderer::CreateMesh(const char* meshName, void* pVertexList, UINT vertexSize, UINT vertexStride, void* pIndexList, UINT indexSize, USHORT indexStride)
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

IMaterial* CRenderer::CreateMaterial(const char* name)
{
	CMaterial* pMaterial = new CMaterial;
	pMaterial->m_pRenderer = this;

	m_mapMaterial.insert({ name,pMaterial });
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

ShaderData* CRenderer::GetShader(const WCHAR* wszName)
{
	if (m_mapShader.find(wszName) == m_mapShader.end())
		__debugbreak();

	return m_mapShader[wszName];
}

ID3D11ShaderResourceView* CRenderer::GetShaderResourceView(const WCHAR* wszTexFile)
{
	if (m_mapSRV.find(wszTexFile) == m_mapSRV.end())
		__debugbreak();

	return m_mapSRV[wszTexFile];
}

ID3D11RasterizerState* CRenderer::GetRasterizer(const char* szName)
{
	if (m_mapRasterizer.find(szName) == m_mapRasterizer.end())
		__debugbreak();

	return m_mapRasterizer[szName];
}

ID3D11SamplerState* CRenderer::GetSampler(const char* szName)
{
	if (m_mapSampler.find(szName) == m_mapSampler.end())
		__debugbreak();

	return m_mapSampler[szName];
}

ID3D11DepthStencilState* CRenderer::GetDepthStencil(const char* szName)
{
	if (m_mapDepthStencil.find(szName) == m_mapDepthStencil.end())
		__debugbreak();

	return m_mapDepthStencil[szName];
}

ID3D11BlendState* CRenderer::GetBlend(const char* szName)
{
	if (m_mapBlend.find(szName) == m_mapBlend.end())
		__debugbreak();

	return m_mapBlend[szName];
}
