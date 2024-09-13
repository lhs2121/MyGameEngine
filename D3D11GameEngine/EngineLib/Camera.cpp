#include "Pre.h"
#include "Camera.h"
#include "Renderer.h"
#include "Scene.h"

void Camera::Awake()
{
	transform.SetPos({ 0,0,-500 });
	windowSize = { Window::GetSizeX(),Window::GetSizeY()};
}

void Camera::AddRenderer(Renderer* _renderer,int _renderOrder)
{
	if (rendererMap.find(_renderOrder) != rendererMap.end())
	{
		std::list<Renderer*> newRendererList;
		rendererMap.insert({ _renderOrder, std::move(newRendererList) });
	}
	rendererMap[_renderOrder].push_back(_renderer);
}

void Camera::DeleteRenderer(Renderer* _renderer)
{
	rendererMap[_renderer->GetRenderOrder()].remove(_renderer);
}

void Camera::ChangeRenderOrder(Renderer* _renderer, int _afterOrder)
{
	int beforeOrder = _renderer->GetRenderOrder();
	rendererMap[beforeOrder].remove(_renderer);

	AddRenderer(_renderer, _afterOrder);
}

void Camera::Update(float _deltaTime)
{
}

void Camera::Render()
{
	transform.viewMat.View(transform.worldPosition, eyeDir, eyeUp);

	switch (projectionType)
	{
	case ProjectionType::Perspective:
		transform.projectionMat.Perspective(fovY, windowSize.x, windowSize.y, Near, Far);
		break;
	case ProjectionType::Orthographic:
		transform.projectionMat.Orthographic(windowSize.x, windowSize.y, Near, Far);
		break;
	}

	for (auto& pair : rendererMap)
	{
		std::list<Renderer*> rendererList = pair.second;
		for (Renderer* renderer : rendererList)
		{
			renderer->transform.SetWorldViewProjection(transform.viewMat, transform.projectionMat);
			renderer->Render();
		}
	}
}
