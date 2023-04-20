#include "object2d.h"
#include "application.h"
#include "gaugeframe.h"
#include "texture.h"

//
//”wŒi‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^
//
CGaugeFrame::CGaugeFrame()
{
}

//
//”wŒi‚ÌƒfƒXƒgƒ‰ƒNƒ^
//
CGaugeFrame::~CGaugeFrame()
{
}

//
//”wŒi‚Ì¶¬
//
CGaugeFrame * CGaugeFrame::Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale)
{
	CGaugeFrame *pCharUI = nullptr;
	pCharUI = new CGaugeFrame;

	//ƒkƒ‹ƒ`ƒFƒbƒN
	if (pCharUI != nullptr)
	{
		pCharUI->m_apObject2D = new CObject2D;

		pCharUI->SetPos(pos);
		pCharUI->SetScale(scale);
		pCharUI->Init();
		pCharUI->SetType(CObject::OBJTYPE_BG);
	}

	return pCharUI;
}

//
//”wŒi‚Ì‰Šú‰»ˆ—
//
HRESULT CGaugeFrame::Init()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->SetPos(GetPos());
		m_apObject2D->SetScale(m_scale.x, m_scale.y);
		m_apObject2D->SetCol(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		m_apObject2D->Init();
		m_apObject2D->SetTexture(CTexture::TEXTURE_GAUGEFRAME);
	}

	return S_OK;
}

//
//”wŒi‚ÌI—¹ˆ—
//
void CGaugeFrame::Uninit()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Uninit();
		Release();
	}
}

//
//”wŒi‚ÌXVˆ—
//
void CGaugeFrame::Update()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Update();
		m_col = m_apObject2D->GetCol();
		m_scale = m_apObject2D->GetScale();

		m_apObject2D->SetCol(m_col);
		m_apObject2D->SetScale(m_scale.x, m_scale.y);
	}
}

//
//”wŒi‚Ì•`‰æˆ—
//
void CGaugeFrame::Draw()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Draw();
	}
}