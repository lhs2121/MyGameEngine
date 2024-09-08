#include "Pre.h"
#include "TestActor.h"

void TestActor::Awake()
{
	EngineDirectory dir;
	std::vector<EngineFile> files = dir.GetAllFileExt(".png");

	if(nullptr == ResManager->Find(ResType::Texture, "TestTexture"))
	{
		ITexture* tex = (ITexture*)ResManager->CreateResource(ResType::Texture, "TestTexture");
		tex->Setting(files[0]);
	}
	m_pSpriteRenderer = (SpriteRenderer*)CreateObject(new SpriteRenderer());
	m_pSpriteRenderer->SetTexture("TestTexture");
	m_pSpriteRenderer->CreateAnimation(2, 2, 1.0f);
	
	m_pColider2D = (Colider2D*)CreateObject(new Colider2D());
	m_pColider2D->SetColScale({64,64,1,1});

}

void TestActor::Update(float _Delta)
{
	if (m_pColider2D->IsCollision)
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
	m_pColider2D->ColScale = _Scale;
}

void TestActor::SetColType(ColType _Type)
{
	m_pColider2D->SetColType(_Type);
}
