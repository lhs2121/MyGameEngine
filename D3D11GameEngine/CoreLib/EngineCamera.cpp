#include "Pre.h"
#include "EngineCamera.h"
#include "EngineRenderer.h"

void EngineCamera::Awake()
{
	Name = "EngineCamera";
	WindowSize = Window->GetWindowSize();
}

void EngineCamera::PushRenderer(EngineRenderer* Renderer)
{
	RendererList.push_back(Renderer);
}

void EngineCamera::Update(float _Delta)
{

}

void EngineCamera::Render()
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
