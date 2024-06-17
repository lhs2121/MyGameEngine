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
	EngineDirectory dir;
	std::vector<EngineFile> ImageFile;
	dir.GetAllFileExt(&ImageFile,".png");
	
	IEngineD3DManager* ResManager = EngineCore::GetMainD3DManager();
	Texture = ResManager->CreateTexture("TestTexture");

	Texture->Setting(ImageFile[0].GetPath().c_str());

	GetLevel()->GetMainCamera()->SetProjectionType(ProjectionType::Perspective);
	Renderer = CreateComponent<EngineRenderer>();
	Renderer->Transform.SetScale({ 100,100,100 });
}

void TestActor::Update(float _Delta)
{
	if (KeyIsPress('1'))
	{
		Renderer->Transform.AddRotation({ 100 * _Delta,0,0 });
	}
	if (KeyIsPress('2'))
	{
		Renderer->Transform.AddRotation({ 0,-100 * _Delta,0 });
	}
	if (KeyIsPress('3'))
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

	if (KeyIsDown('C'))
	{
		IEngineD3DManager* ResManager = EngineCore::GetMainD3DManager();
		Renderer->VB = ResManager->FindVertexBuffer("Box3D");
		Renderer->IB = ResManager->FindIndexBuffer("Box3D");
		Renderer->VS = ResManager->FindVertexShader("Test3DShader");
		Renderer->IA = ResManager->FindInputLayout("PosColor");
		Renderer->PS = ResManager->FindPixelShader("Test3DShader");
	}
	if (KeyIsDown('V'))
	{
		IEngineD3DManager* ResManager = EngineCore::GetMainD3DManager();
		Renderer->VB = ResManager->FindVertexBuffer("Box2D");
		Renderer->IB = ResManager->FindIndexBuffer("Box2D");
		Renderer->VS = ResManager->FindVertexShader("Test2DShader");
		Renderer->IA = ResManager->FindInputLayout("Pos");
		Renderer->PS = ResManager->FindPixelShader("Test2DShader");
	}
}
