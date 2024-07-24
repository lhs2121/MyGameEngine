#include "Pre.h"
#include "TestActor.h"
#include <BaseLib\BaseAPI.h>
#include <CoreLib\EngineSpriteRenderer.h>
#include <CoreLib\EngineLevel.h>
#include <CoreLib\EngineCamera.h>
#include <CoreLib\Singleton.h>
#include <MediaLib\MediaAPI.h>

void TestActor::Awake()
{
	GetLevel()->GetMainCamera()->SetProjectionType(ProjectionType::Perspective);

	EngineDirectory dir;

	std::vector<EngineFile> ImageFile;
	dir.GetAllFileExt(&ImageFile,".png");
	
	IEngineTexture* Texture = MainD3DManager->CreateTexture("Stand_000");
	Texture->Setting(ImageFile[0]);

	Renderer = (EngineSpriteRenderer*)CreateComponent(new EngineSpriteRenderer);
	Renderer->SetTexture("Stand_000");
	Renderer->CreateAnimation(3,3, 0.1f);
}

void TestActor::Update(float _Delta)
{
	if (MainInput->IsPress('Z'))
	{
		Renderer->Transform.AddRotation({ 100 * _Delta,0,0 });
	}
	if (MainInput->IsPress('X'))
	{
		Renderer->Transform.AddRotation({ 0,100 * _Delta,0 });
	}
	if (MainInput->IsPress('C'))
	{
		Renderer->Transform.AddRotation({ 0,0,100 * _Delta });
	}

	if (MainInput->IsPress('W'))
	{
		Renderer->Transform.AddPos({ 0,100 * _Delta,0 });
	}
	if (MainInput->IsPress('A'))
	{
		Renderer->Transform.AddPos({ -100 * _Delta,0,0 });
	}
	if (MainInput->IsPress('S'))
	{
		Renderer->Transform.AddPos({ 0,-100 * _Delta,0 });
	}
	if (MainInput->IsPress('D'))
	{
		Renderer->Transform.AddPos({ 100 * _Delta,0,0 });
	}
	if (MainInput->IsPress('Q'))
	{
		Renderer->Transform.AddPos({ 0,0,100 * _Delta });
	}
	if (MainInput->IsPress('E'))
	{
		Renderer->Transform.AddPos({ 0,0,-100 * _Delta });
	}
	if (MainInput->IsDown('R'))
	{
		Renderer->Transform.SetPos({ 0,0,0 });
		Renderer->Transform.SetRotation({ 0,0,0 });
	}
}
