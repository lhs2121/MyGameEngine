#include "CollisionAPI.h"
#include "CBoxColider.h"
#include "COriBoxColider.h"
#include "CSphereColider.h"

void CreateBoxColider(IBoxColider** ppCol)
{
	CBoxColider* Col = new CBoxColider;
	*ppCol = Col;
}

void DeleteBoxColider(IBoxColider* pCol)
{
	CBoxColider* pCast = (CBoxColider*)pCol;
	delete pCast;
}

void CreateOriBoxColider(IOriBoxColider** ppCol)
{
	COriBoxColider* Col = new COriBoxColider;
	*ppCol = Col;
}

void DeleteOriBoxColider(IOriBoxColider* pCol)
{
	COriBoxColider* pCast = (COriBoxColider*)pCol;
	delete pCast;
}

void CreateSphereColider(ISphereColider** ppCol)
{
	CSphereColider* Col = new CSphereColider;
	*ppCol = Col;
}

void DeleteSphereColider(ISphereColider* pCol)
{
	CSphereColider* pCast = (CSphereColider*)pCol;
	delete pCast;
}