#include "Pre.h"
#include "Back.h"

void Back::Awake()
{
	transform.SetLocalPos({ 0, 0, 5 });

	pSpriteRenderer = CreateChild<SpriteRenderer>();
	Resource::CreateTexture("back/back.jpg");
	pSpriteRenderer->GetMaterial()->pTexture = Resource::FindTexture("back");

	float w = (float)pSpriteRenderer->GetMaterial()->pTexture->metaData.width;
	float h = (float)pSpriteRenderer->GetMaterial()->pTexture->metaData.height;

	pSpriteRenderer->transform.SetLocalScale({ w,h });
	pSpriteRenderer->CreateAnimation(1, 1, 1.0f);
}

void Back::Update(float _deltaTime)
{

}
