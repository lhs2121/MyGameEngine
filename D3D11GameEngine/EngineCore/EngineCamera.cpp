#include "Pre.h"
#include "EngineCamera.h"
#include "EngineCore.h"

EngineCamera::EngineCamera()
{
}

EngineCamera::~EngineCamera()
{
}

void EngineCamera::Start()
{
	WindowSize = EngineCore::GetMainWindow()->GetWindowSize();
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

	for (EngineRenderer* Renderer : RendererList)
	{
		float4x4 World = Renderer->Transform.WorldMat;
		Renderer->Transform.WorldViewProjectionMat = World * Transform.ViewMat * Transform.ProjectionMat;
		Renderer->Render();
	}
}
