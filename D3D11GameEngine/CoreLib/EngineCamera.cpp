#include "Pre.h"
#include "EngineCamera.h"
#include "EngineRenderer.h"
#include "Singleton.h"

void EngineCamera::Awake()
{
	WindowSize = MainWindow->GetWindowSize();
}

void EngineCamera::PushRenderer(EngineRenderer* Renderer)
{
	RendererList.Add(Renderer);
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

	RendererList.GoFirst();
	for (size_t i = 0; i < RendererList.GetCount(); i++)
	{
		EngineRenderer* Renderer = (EngineRenderer*)RendererList.Item();

		float4x4 world = Renderer->Transform.WorldMat;
		Renderer->Transform.WorldViewProjectionMat = world * Transform.ViewMat * Transform.ProjectionMat;
		Renderer->Render();

		RendererList.GoNext();
	}
}