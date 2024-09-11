#include "Pre.h"
#include "Naming.h"
Naming* Naming::mainNaming = nullptr;

void Naming::Create()
{
	mainNaming = new Naming();
}

void Naming::Delete()
{
	delete mainNaming;
}
