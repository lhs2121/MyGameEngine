#pragma once
#include "EngineLevelObject.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};
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

	void Start() override;
	void Update(float _Delta) override;
	void PushRenderer(EngineRenderer* Renderer);
	void SetProjectionType(ProjectionType _Type)
	{
		m_ProjectionType = _Type;
	}
	void Render();
private:
	ProjectionType m_ProjectionType = ProjectionType::Orthographic;
	float4 WindowSize;
	float FovY = 60.0f;
	float Near = 0.1f;
	float Far = 1000.0f;

	std::list<EngineRenderer*> RendererList;
	float4 EyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
	float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
	float4 EyeUp = { 0.0f, 1.0f, 0.0f, 1.0f };
};