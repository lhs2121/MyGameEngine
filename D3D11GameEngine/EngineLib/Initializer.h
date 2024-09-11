#pragma once

class Engine;
struct Initializer
{
	virtual void CreateAllScene(Engine* pMainEngine) = 0;
};