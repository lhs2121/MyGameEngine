#include "Pre.h"
#include "Ground.h"

void Ground::Awake()
{	
	SetName("Ground");
	transform.SetLocalScale({ 64,64 });

	Input::AddUser(this);
}

void Ground::Update(float _deltaTime)
{
}
