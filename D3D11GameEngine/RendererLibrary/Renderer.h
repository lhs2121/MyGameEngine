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
public:
	~CRenderer();
	void Initialize(UINT windowSizeX, UINT windowSizeY, HWND& hwnd) override;
	void StartRender() override;
	void EndRender() override;

	ISpriteObject* CreateSpriteObject(const char* name, const WCHAR* wszTexfile, int countX, int countY, float interTime = 0.3f);
	IMesh* CreateMesh(const char* meshName, void* pVertexList, UINT vertexSize, UINT vertexStride, void* pIndexList, UINT indexSize, USHORT indexStride);
	IMaterial* CreateMaterial(const char* name) override;
	CConstantBuffer* CreateConstantBuffer(const char* bufferName, void* pData, UINT dataSize, const char* szTargerShader, int slotNum);

	void LoadTexture(const WCHAR* wszFilePath) override;
	void LoadShader(const WCHAR* wszShaderPath) override;
	
	void DrawRect(const XMMATRIX& matWorld, const XMVECTOR& color) override;
	void DrawRect2(float x, float y, float width, float height, const XMVECTOR& color) override;
	void DrawSprite(const XMMATRIX& matWorld, ISpriteObject* pSpriteObject) override;

	ShaderData* GetShader(const WCHAR* wszName);
	ID3D11ShaderResourceView* GetShaderResourceView(const WCHAR* wszTexFile);
	ID3D11RasterizerState* GetRasterizer(const char* szName);
	ID3D11SamplerState* GetSampler(const char* szName);
	ID3D11DepthStencilState* GetDepthStencil(const char* szName);
	ID3D11BlendState* GetBlend(const char* szName);

private:
	void CreateBasicMesh();
	void CreateBasicMaterial();
	std::unordered_map<std::wstring, ShaderData*> m_mapShader;
	std::unordered_map<std::wstring, ID3D11ShaderResourceView*> m_mapSRV;
	std::unordered_map<std::string,  ID3D11RasterizerState*> m_mapRasterizer;
	std::unordered_map<std::string,  ID3D11DepthStencilState*> m_mapDepthStencil;
	std::unordered_map<std::string,  ID3D11BlendState*> m_mapBlend;
	std::unordered_map<std::string,  ID3D11SamplerState*> m_mapSampler;
	std::unordered_map<std::string,  CSpriteObject*> m_mapSpriteObject;
	std::unordered_map<std::string,  CMesh*> m_mapMesh;
	std::unordered_map<std::string,  CMaterial*> m_mapMaterial;


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
};