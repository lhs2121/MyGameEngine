#include "Pre.h"
#include "Camera.h"
#include "Renderer.h"

void Camera::Awake()
{
	Name = "Camera";
	WindowSize = Window->GetWindowSize();
}

void Camera::PushRenderer(Renderer* Renderer)
{
	RendererList.push_back(Renderer);
}

void Camera::Update(float _Delta)
{

}

void Camera::Render()
{
	Transform.ViewMat.View(EyePos, EyeDir, EyeUp);

	switch (m_ProjectionType)
	{
	case ProjectionType::Perspective:
		Transform.ProjectionMat.Perspective(FovY, WindowSize.x, WindowSize.y, Near, Far);
		break;
	case ProjectionType::Orthographic:
		Transform.ProjectionMat.Orthographic(WindowSize.x, WindowSize.y, Near, Far);
		break;
	}

	for (auto Renderer : RendererList)
	{
		float4x4 world = Renderer->Transform.WorldMat;
		Renderer->Transform.WorldViewProjectionMat = world * Transform.ViewMat * Transform.ProjectionMat;
		Renderer->Render();
	}
}
