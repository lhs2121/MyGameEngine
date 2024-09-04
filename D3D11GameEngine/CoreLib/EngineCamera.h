#pragma once
#include "EngineObject.h"
#include "EngineRenderer.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};
class CoreAPI EngineCamera : public EngineObject
{
public:
	void Awake() override;
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
	float Far  = 10000.0f;

	EngineList RendererList;
	float4 EyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
	float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
	float4 EyeUp  = { 0.0f, 1.0f, 0.0f, 1.0f };
};