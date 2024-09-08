#pragma once
#include "GameObject.h"
#include "Renderer.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};
class Camera : public GameObject
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;
	void PushRenderer(Renderer* Renderer);
	void SetProjectionType(ProjectionType _type)
	{
		projectionType = _type;
	}
	void Render();
private:
	ProjectionType projectionType = ProjectionType::Orthographic;
	float4 windowSize;

	float fovY = 60.0f;
	float Near = 0.1f;
	float Far  = 10000.0f;

	std::list<Renderer*> rendererList;
	float4 eyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
	float4 eyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
	float4 eyeUp  = { 0.0f, 1.0f, 0.0f, 1.0f };
};