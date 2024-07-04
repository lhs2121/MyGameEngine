#include "Pre.h"
#include "TestActor.h"
#include "EngineCore\EngineCamera.h"

TestActor::TestActor()
{
}

TestActor::~TestActor()
{
}

void TestActor::Start()
{
	GetLevel()->GetMainCamera()->SetProjectionType(ProjectionType::Perspective);

	EngineDirectory dir;
	dir.GoBase();

	std::vector<EngineFile> ImageFile;
	dir.GetAllFileExt(&ImageFile,".png");
	
	IEngineD3DManager* ResManager = EngineCore::GetMainD3DManager();
		
	IEngineTexture* Texture = ResManager->CreateTexture("Stand_000");
	Texture->Setting(ImageFile[0]);

	Renderer = CreateComponent<EngineSpriteRenderer>();
	Renderer->SetTexture("Stand_000");
	Renderer->CreateAnimation(1,1, 0.1f);
}

void TestActor::Update(float _Delta)
{
	if (KeyIsPress('Z'))
	{
		Renderer->Transform.AddRotation({ 100 * _Delta,0,0 });
	}
	if (KeyIsPress('X'))
	{
		Renderer->Transform.AddRotation({ 0,100 * _Delta,0 });
	}
	if (KeyIsPress('C'))
	{
		Renderer->Transform.AddRotation({ 0,0,100 * _Delta });
	}

	if (KeyIsPress('W'))
	{
		Renderer->Transform.AddPos({ 0,100 * _Delta,0 });
	}
	if (KeyIsPress('A'))
	{
		Renderer->Transform.AddPos({ -100 * _Delta,0,0 });
	}
	if (KeyIsPress('S'))
	{
		Renderer->Transform.AddPos({ 0,-100 * _Delta,0 });
	}
	if (KeyIsPress('D'))
	{
		Renderer->Transform.AddPos({ 100 * _Delta,0,0 });
	}

	if (KeyIsPress('Q'))
	{
		Renderer->Transform.AddPos({ 0,0,100 * _Delta });
	}
	if (KeyIsPress('E'))
	{
		Renderer->Transform.AddPos({ 0,0,-100 * _Delta });
	}

	if (KeyIsDown('R'))
	{
		Renderer->Transform.SetPos({ 0,0,0 });
		Renderer->Transform.SetRotation({ 0,0,0 });
	}
}
