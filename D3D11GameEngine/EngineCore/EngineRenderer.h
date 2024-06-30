#pragma once
#include <d3d11.h>
#include "EngineTransform.h"
#include "EngineComponent.h"

struct SpriteData
{
	float2 ResizeRatio = { 1.0f,1.0f };
	float2 Offset = { 0.0f,0.0f };
};

class EngineRenderer : public EngineComponent
{
public:
	// constrcuter destructer
	EngineRenderer();
	~EngineRenderer();

	// delete Function
	EngineRenderer(const EngineRenderer& _Other) = delete;
	EngineRenderer(EngineRenderer&& _Other) noexcept = delete;
	EngineRenderer& operator=(const EngineRenderer& _Other) = delete;
	EngineRenderer& operator=(EngineRenderer&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _Delta) override;

	virtual void Render();

	void BindTexture(EngineString _Name);
	void BindSampler(EngineString _Name);
	void BindTransform();
	void BindSpriteData();

	void CreateAnimation(int _SpriteCountX,int _SpriteCountY);

	
	int SpriteCountX;
	int SpriteCountY;

	int CurSpriteX = 0;
	int CurSpriteY = 0;

	int CurFrame = 0;

	float InterTime = 0.5f;
	float CurTime;

	std::vector<std::vector<SpriteData>>* SpriteDatas = nullptr;
	SpriteData* CurSpriteData = nullptr;

	IEngineVertexBuffer* VB = nullptr;
	IEngineIndexBuffer* IB = nullptr;
	IEngineInputLayout* IA = nullptr;
	IEngineVertexShader* VS = nullptr;
	IEngineRasterizer* RS = nullptr;
	IEnginePixelShader* PS = nullptr;
	IEngineDepthStencil* DS = nullptr;
	IEngineTexture* CurTexture = nullptr;

	ID3D11Buffer* TransformBuffer = nullptr;
	ID3D11Buffer* SpriteDataBuffer = nullptr;
};	


