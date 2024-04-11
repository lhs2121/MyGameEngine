#pragma once
#include "EngineLevelObject.h"
class EngineCamera : public EngineLevelObject
{
public:
	// constrcuter destructer
	EngineCamera();
	~EngineCamera();

	// delete Function
	EngineCamera(const EngineCamera& _Other) = delete;
	EngineCamera(EngineCamera&& _Other) noexcept = delete;
	EngineCamera& operator=(const EngineCamera& _Other) = delete;
	EngineCamera& operator=(EngineCamera&& _Other) noexcept = delete;

	void PushRenderer(EngineRenderer* Renderer);
	void Update(float _Delta) override;
	void Render();
private:
	std::list<EngineRenderer*> RendererList;
	float4 EyePos = { 0.0f,0.0f,-500.0f };
	float4 LookAtPoint = { 0.0f,0.0f,0.0f };
	float4 UpDirection = { 0.0f,1.0f,0.0f };
};