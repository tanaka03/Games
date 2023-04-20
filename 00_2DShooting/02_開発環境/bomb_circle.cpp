#include "bomb_circle.h"
#include "object2d.h"

CBombCircle::CBombCircle()
{
}

CBombCircle::~CBombCircle()
{
}

HRESULT CBombCircle::Init()
{
	CObject2D::Init();
	return S_OK;
}

void CBombCircle::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CBombCircle::Update()
{
	CObject2D::Update();
}

void CBombCircle::Draw()
{
	CObject2D::Draw();
}