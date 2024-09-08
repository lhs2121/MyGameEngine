#include "Pre.h"
#include "Camera.h"
#include "Renderer.h"

void Camera::Awake()
{
	windowSize = mainWindow->GetWindowSize();
}

void Camera::PushRenderer(Renderer* Renderer)
{
	rendererList.push_back(Renderer);
}

void Camera::Update(float _deltaTime)
{
}

void Camera::Render()
{
	transform.viewMat.View(eyePos, eyeDir, eyeUp);

	switch (projectionType)
	{
	case ProjectionType::Perspective:
		transform.projectionMat.Perspective(fovY, windowSize.x, windowSize.y, Near, Far);
		break;
	case ProjectionType::Orthographic:
		transform.projectionMat.Orthographic(windowSize.x, windowSize.y, Near, Far);
		break;
	}

	for (auto renderer : rendererList)
	{
		renderer->transform.SetWorldViewProjection(transform.viewMat, transform.projectionMat);
		renderer->Render();
	}
}
