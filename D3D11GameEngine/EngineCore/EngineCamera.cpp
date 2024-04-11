#include "Pre.h"
#include "EngineCamera.h"

EngineCamera::EngineCamera()
{
}

EngineCamera::~EngineCamera()
{
}

void EngineCamera::PushRenderer(EngineRenderer* Renderer)
{
	RendererList.push_back(Renderer);
}

void EngineCamera::Update(float _Delta)
{
	Transform.view
}

void EngineCamera::Render()
{
	for (EngineRenderer* Renderer : RendererList)
	{
		Renderer->Render();
	}
}
