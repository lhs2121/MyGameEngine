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

}

void EngineCamera::PushRenderer(EngineRenderer* Renderer)
{
	RendererList.push_back(Renderer);
}

void EngineCamera::Update(float _Delta)
{
	Transform.View(EyePos, EyeDir, EyeUp);

	for (EngineRenderer* Renderer : RendererList)
	{
		float4x4 World = Renderer->Transform.WorldMat;
		float4x4 View = Transform.ViewMat;
		Renderer->Transform.WorldViewProjectionMat = World * View;
	}
}

void EngineCamera::Render()
{
	for (EngineRenderer* Renderer : RendererList)
	{
		Renderer->Render();
	}
}
