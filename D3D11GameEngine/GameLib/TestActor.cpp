#include "Pre.h"
#include "TestActor.h"

void TestActor::Awake()
{
	EngineDirectory dir;
	std::vector<EngineFile> files = dir.GetAllFileExt(".png");

	if(nullptr == ResManager->Find(ResType::Texture, "TestTexture"))
	{
		ITexture* tex = (ITexture*)ResManager->CreateResource(Device,ResType::Texture, "TestTexture");
		tex->Setting(Device->GetDevice(),files[0]);
	}
	Renderer = (EngineSpriteRenderer*)CreateObject(new EngineSpriteRenderer());
	Renderer->SetTexture("TestTexture");
	Renderer->CreateAnimation(2, 2, 1.0f);

	Col = (EngineCollision*)CreateObject(new EngineCollision());
	Col->ColScale = Renderer->Transform.LocalScale;
}

void TestActor::Update(float _Delta)
{
	if (Col->IsCollision)
	{
		int a = 0;
	}
	if (Input->IsPress('Z', this))
	{
		Transform.AddRotation({ 100 * _Delta,0,0 });
	}
	if (Input->IsPress('X', this))
	{
		Transform.AddRotation({ 0,100 * _Delta,0 });
	}
	if (Input->IsPress('C', this))
	{
		Transform.AddRotation({ 0,0,100 * _Delta });
	}
	if (Input->IsPress('W', this))
	{
		Transform.AddPos({ 0,100 * _Delta,0 });
	}
	if (Input->IsPress('A', this))
	{
		Transform.AddPos({ -100 * _Delta,0,0 });
	}
	if (Input->IsPress('S', this))
	{
		Transform.AddPos({ 0,-100 * _Delta,0 });
	}
	if (Input->IsPress('D', this))
	{
		Transform.AddPos({ 100 * _Delta,0,0 });
	}
	if (Input->IsPress('Q', this))
	{
		Transform.AddPos({ 0,0,100 * _Delta });
	}
	if (Input->IsPress('E', this))
	{
		Transform.AddPos({ 0,0,-100 * _Delta });
	}
	if (Input->IsDown('R', this))
	{
		Transform.SetPos({ 0,0,0 });
		Transform.SetRotation({ 0,0,0 });
	}
}

void TestActor::SetColScale(float4 _Scale)
{
	Col->ColScale = _Scale;
}

void TestActor::SetColType(ColType _Type)
{
	Col->SetColType(_Type);
}
