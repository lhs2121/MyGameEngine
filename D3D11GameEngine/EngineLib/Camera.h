#pragma once

#include "Renderer.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};
class Camera : public Object
{
public:
	void Awake() override;
	void Update(float _deltaTime) override;
	void AddRenderer(Renderer* _renderer, int _renderOrder = 0);
	void DeleteRenderer(Renderer* _renderer);
	void ChangeRenderOrder(Renderer* _renderer, int _afterOrder);
	void SetProjectionType(ProjectionType _type) { projectionType = _type; }
	void Render();
private:
	XMVECTOR eyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
	XMVECTOR eyeUp = { 0.0f, 1.0f, 0.0f, 1.0f };

	float fovYDegree = 60.0f;
	float Near = 0.3f;
	float Far = 1000.0f;


	float4 windowSize;

	ProjectionType projectionType = ProjectionType::Orthographic;

	std::map<int, std::list<Renderer*>> rendererMap;
};