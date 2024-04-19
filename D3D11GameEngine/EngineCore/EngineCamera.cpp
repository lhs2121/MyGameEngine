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
	Transform.View(EyePos, EyeDir, EyeUp);


	for (EngineRenderer* Renderer : RendererList)
	{
		float4x4 World = Renderer->Transform.WorldMat;
		float4x4 View = Transform.ViewMat; 
		float4x4 Projection;
		Projection.Projection(WindowSize.x, WindowSize.y, Near, Far);
		Renderer->Transform.WorldViewProjectionMat = World * View * Projection;
		float4x4 WVP = Renderer->Transform.WorldViewProjectionMat;
		Renderer->Render();
	}
}
