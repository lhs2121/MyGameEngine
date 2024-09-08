#pragma once
#include "Object.h"
#include "Renderer.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};
class  Camera : public Object
{
public:
	void Awake() override;
	void Update(float _Delta) override;
	void PushRenderer(Renderer* Renderer);
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

	std::list<Renderer*> RendererList;
	float4 EyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
	float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
	float4 EyeUp  = { 0.0f, 1.0f, 0.0f, 1.0f };
};