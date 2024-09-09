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
	void AddRenderer(Renderer* _renderer, int _renderOrder = 0);
	void ChangeRenderOrder(Renderer* _renderer, int _afterOrder);
	void SetProjectionType(ProjectionType _type) { projectionType = _type; }
	void Render();
private:
	float fovY = 60.0f;
	float Near = 0.1f;
	float Far = 10000.0f;

	float4 eyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
	float4 eyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
	float4 eyeUp = { 0.0f, 1.0f, 0.0f, 1.0f };

	float4 windowSize;

	ProjectionType projectionType = ProjectionType::Orthographic;

	std::map<int, std::list<Renderer*>> rendererMap;
};