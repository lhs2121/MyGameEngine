#pragma once
#include "IRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "SpriteObject.h"

#include <unordered_map>
#include <string>

class CRenderer : public IRenderer
{
	friend class CMaterial;
public:
	~CRenderer();
	void Initalize(UINT windowSizeX, UINT windowSizeY, HWND& hwnd) override;
	void StartRender() override;
	void EndRender() override;

	ISpriteObject* CreateSpriteObject(const char* name);

	CMesh* CreateMesh(const char* meshName, void* pVertexList, UINT vertexSize, UINT vertexStride, 
		void* pIndexList, UINT indexSize, USHORT indexStride);

	IMaterial* CreateMaterial(const char* materialName, const WCHAR* wszShaderName, const WCHAR* wszTexFileName);

	CConstantBuffer* CreateConstantBuffer(const char* bufferName, void* pData, UINT dataSize, const char* szTargerShader, int slotNum);

	ID3D11ShaderResourceView* GetShaderResourceView(const WCHAR* wszTexFile);

	void LoadTexture(const WCHAR* wszFilePath) override;
	void LoadShader(const WCHAR* wszShaderPath) override;
	
	void DrawRect(const XMMATRIX& matWorld, const XMVECTOR& color) override;
	void DrawSprite(const XMMATRIX& matWorld, ISpriteObject* pSpriteObject) override;
private:
	void CreateBasicMesh();
	void CreateBasicMaterial();

	std::unordered_map<const char*, CMesh*> m_mapMesh;
	std::unordered_map<const char*, CMaterial*> m_mapMaterial;
	std::unordered_map<const char*, CSpriteObject*> m_mapSpriteObject;
	std::unordered_map<std::wstring, ID3D11ShaderResourceView*> m_mapTexture;
	std::unordered_map<std::wstring, ShaderData*> m_mapShader;

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

	//ID3D11BlendState* m_pPrevBlendState = nullptr;
	//ID3D11SamplerState* m_pPrevSamplerState = nullptr;
	//ID3D11RasterizerState* m_pPrevRasterizerState = nullptr;
	//ID3D11DepthStencilState* m_pPrevDepthStencilState = nullptr;

	ID3D11RasterizerState* m_pRasterizerState_Solid;
	ID3D11RasterizerState* m_pRasterizerState_WireFrame;
	ID3D11SamplerState* m_pSamplerState_Point;
	ID3D11DepthStencilState* m_pDepthStencilState_Depth_On;
	ID3D11BlendState* m_pBlendState_Alhpa_On;
		
	CConstantBuffer* m_pConstantBuffer_transform;
	CConstantBuffer* m_pConstantBuffer_color;

	ID3D11InputLayout* m_pBasicInputLayout = nullptr;
	CMesh* m_pRect2D = nullptr;
	CMesh* m_pRect3D = nullptr;
	CMaterial* m_pBasicColor = nullptr;
	CMaterial* m_pBasicSprite2D = nullptr;
};