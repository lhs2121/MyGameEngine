#pragma once
#include "IRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "SpriteObject.h"

#include <unordered_map>
#include <string>

struct SimpleVertex
{
	float4 POSITION;
	float2 TEXCOORD;
};

class CRenderer : public IRenderer
{
public:
	~CRenderer();
	void Initalize(UINT windowSizeX, UINT windowSizeY, HWND& hwnd) override;
	void StartRender() override;
	void EndRender() override;
	ISpriteObject* CreateSpriteObject(const char* name);

	CMesh* CreateMesh(const char* meshName, void* pVertexList, UINT vertexSize, UINT vertexStride, void* pIndexList, UINT indexSize, USHORT indexStride);

	CMaterial* CreateMaterial(const char* materialName, const WCHAR* wszShaderPath, const WCHAR* wszTexFileName, D3D11_RASTERIZER_DESC* pRsDesc,
		D3D11_SAMPLER_DESC* pSamplerDesc, D3D11_BLEND_DESC* pBlendDesc, D3D11_DEPTH_STENCIL_DESC* pDsDesc);

	CConstantBuffer* CreateConstantBuffer(const char* bufferName, void* pData, UINT dataSize, const char* szTargerShader, int slotNum);

	void LoadTexture(const WCHAR* wszFilePath) override;
	void LoadShader(const WCHAR* wszShaderPath) override;
	
	void DrawRect(const XMMATRIX& matWorld, const XMVECTOR& color) override;
	void DrawSprite(const XMMATRIX& matWorld, ISpriteObject* pSpriteObject) override;

	void SetTexture(const WCHAR* wszFile, IMaterial* pMaterial) override;
private:
	void CreateBasicMesh();
	void CreateBasicMaterial();

	std::unordered_map<const char*, CMesh*> m_mapMesh;
	std::unordered_map<const char*, CMaterial*> m_mapMaterial;
	std::unordered_map<const char*, CSpriteObject*> m_mapSpriteObject;
	std::unordered_map<std::wstring, ID3D11ShaderResourceView*> m_mapTexture;
	std::unordered_map<std::wstring, std::pair<ID3D11VertexShader*, ID3D11PixelShader*>> m_mapShader;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	IDXGISwapChain* m_pSwapChain;
	ID3D11Texture2D* m_pRenderTargetBuffer;
	ID3D11Texture2D* m_pDepthStencilBuffer;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11RenderTargetView* m_pRenderTargetView;
	FLOAT m_clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	XMVECTOR m_CameraPosition = { 0.0f, 0.0f, -500.0f, 1.0f };
	XMVECTOR m_CameraEyeDirection = { 0.0f ,0.0f, 1.0f, 1.0f };
	XMVECTOR m_CameraUpDirection = { 0.0f ,1.0f, 0.0f, 1.0f };
	float m_degFovY = 60.0f;
	float m_near = 0.3f;
	float m_far = 1000.0f;

	XMVECTOR m_color;
	XMMATRIX m_matWorld;
	XMMATRIX m_matView;
	XMMATRIX m_matProjection;


	CConstantBuffer* m_pConstantBuffer_transform;
	CConstantBuffer* m_pConstantBuffer_color;
	ID3D11InputLayout* m_pBasicInputLayout = nullptr;
	CMesh* m_pRect2D = nullptr;
	CMesh* m_pRect3D = nullptr;
	CMaterial* m_pBasicColor = nullptr;
	CMaterial* m_pBasicSprite2D = nullptr;
};