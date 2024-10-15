#include "Pre.h"
#include "Camera.h"
#include "Renderer.h"
#include "Scene.h"

void Camera::Awake()
{
	transform.SetLocalPosition({ 0,0,-500 });
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

void Camera::RemoveRenderer(Renderer* _renderer)
{
	int order = _renderer->GetRenderOrder();
	rendererMap[order].remove(_renderer);
	if (rendererMap[order].empty())
	{
		rendererMap.erase(order);
	}
}

void Camera::ChangeRenderOrder(Renderer* _renderer, int _newOrder)
{
	RemoveRenderer(_renderer);
	AddRenderer(_renderer, _newOrder);
}

void Camera::Update(float _deltaTime)
{
}

void Camera::Render()
{
	windowSize = { Window::GetSizeX(),Window::GetSizeY() };
	transform.matView = XMMatrixLookToLH(transform.vecLocalPosition, eyeDir, eyeUp);
	switch (projectionType)
	{
	case ProjectionType::Perspective:
		transform.matProjection = XMMatrixPerspectiveFovLH(fovYDegree * Deg2Rad, windowSize.x/windowSize.y, Near, Far);
		break;
	case ProjectionType::Orthographic:
		transform.matProjection = XMMatrixOrthographicLH(windowSize.x, windowSize.y, Near, Far);
		break;
	}

	for (auto& pair : rendererMap)
	{
		std::list<Renderer*> rendererList = pair.second;
		for (Renderer* renderer : rendererList)
		{
			renderer->transform.matView = transform.matView;
			renderer->transform.matProjection = transform.matProjection;
			renderer->Render();
		}
	}
}
