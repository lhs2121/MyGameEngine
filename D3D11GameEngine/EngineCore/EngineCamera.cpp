#include "Pre.h"
#include "EngineCamera.h"

EngineCamera::EngineCamera()
{
}

EngineCamera::~EngineCamera()
{
}

void EngineCamera::Start()
{
	WindowSize = EngineCore::GetMainWindow().GetWindowSize();
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
	Transform.ProjectionMat.Projection(WindowSize.x, WindowSize.y, Near, Far);
	for (EngineRenderer* Renderer : RendererList)
	{
		float4x4 World = Renderer->Transform.WorldMat;
		Renderer->Transform.WorldViewProjectionMat = World * Transform.ViewMat * Transform.ProjectionMat;
		Renderer->Render();
	}
}
