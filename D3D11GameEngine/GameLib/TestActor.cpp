#include "Pre.h"
#include "TestActor.h"

void TestActor::Awake()
{
	EngineDirectory dir;
	std::vector<EngineFile> files = dir.GetAllFileExt(".png");

	if (nullptr == mainResManager->Find(ResType::Texture, "TestTexture"))
	{
		ITexture* tex = (ITexture*)mainResManager->CreateResource(ResType::Texture, "TestTexture");
		tex->Setting(files[0]);
	}
	pSpriteRenderer = AddComponent<SpriteRenderer>();
	pSpriteRenderer->SetTexture("TestTexture");
	pSpriteRenderer->CreateAnimation(2, 2, 1.0f);

	pColider2D = AddComponent<Colider2D>();
	pColider2D->SetColScale({ 64,64,1,1 });

}

void TestActor::Update(float _deltaTime)
{
	if (pColider2D->isCollision)
	{
		int a = 0;
	}
	if (GetKeyPress('Z'))
	{
		transform.AddRotation({ 100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('X'))
	{
		transform.AddRotation({ 0,100 * _deltaTime,0 });
	}
	if (GetKeyPress('C'))
	{
		transform.AddRotation({ 0,0,100 * _deltaTime });
	}
	if (GetKeyPress('W'))
	{
		transform.AddPos({ 0,100 * _deltaTime,0 });
	}
	if (GetKeyPress('A'))
	{
		transform.AddPos({ -100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('S'))
	{
		transform.AddPos({ 0,-100 * _deltaTime,0 });
	}
	if (GetKeyPress('D'))
	{
		transform.AddPos({ 100 * _deltaTime,0,0 });
	}
	if (GetKeyPress('Q'))
	{
		transform.AddPos({ 0,0,100 * _deltaTime });
	}
	if (GetKeyPress('E'))
	{
		transform.AddPos({ 0,0,-100 * _deltaTime });
	}
	if (GetKeyDown('R'))
	{
		transform.SetPos({ 0,0,0 });
		transform.SetRotation({ 0,0,0 });
	}
}
