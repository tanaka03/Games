#include "landmine.h"
#include "object2d.h"

CLandmine::CLandmine()
{
}

CLandmine::~CLandmine()
{
}

HRESULT CLandmine::Init()
{
	CObject2D::Init();
	return S_OK;
}

void CLandmine::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CLandmine::Update()
{
	CObject2D::Update();
}

void CLandmine::Draw()
{
	CObject2D::Draw();
}