#include "object2d.h"
#include "application.h"
#include "char_ui.h"
#include "texture.h"

//
//”wŒi‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^
//
CCharUI::CCharUI()
{
	m_bRank = false;
}

//
//”wŒi‚ÌƒfƒXƒgƒ‰ƒNƒ^
//
CCharUI::~CCharUI()
{
}

//
//”wŒi‚Ì¶¬
//
CCharUI * CCharUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, ECharType type, ECharState state)
{
	CCharUI *pCharUI = nullptr;
	pCharUI = new CCharUI;

	//ƒkƒ‹ƒ`ƒFƒbƒN
	if (pCharUI != nullptr)
	{
		pCharUI->m_apObject2D = new CObject2D;

		pCharUI->SetPos(pos);
		pCharUI->SetScale(scale);
		pCharUI->SetCharUI(type);
		pCharUI->SetCharState(state);
		pCharUI->Init();
		pCharUI->SetType(CObject::OBJTYPE_BG);
	}

	return pCharUI;
}

CCharUI * CCharUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, int type, ECharState state)
{
	CCharUI *pCharUI = nullptr;
	pCharUI = new CCharUI;

	//ƒkƒ‹ƒ`ƒFƒbƒN
	if (pCharUI != nullptr)
	{
		pCharUI->m_apObject2D = new CObject2D;

		pCharUI->SetPos(pos);
		pCharUI->SetScale(scale);
		pCharUI->SetCharUI((CCharUI::ECharType)type);
		pCharUI->SetCharState(state);
		pCharUI->Init();
		pCharUI->SetType(CObject::OBJTYPE_BG);
	}

	return pCharUI;
}

//
//”wŒi‚Ì‰Šú‰»ˆ—
//
HRESULT CCharUI::Init()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->SetPos(GetPos());
		m_apObject2D->SetScale(m_scale.x, m_scale.y);
		m_apObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apObject2D->Init();

		switch (m_UI)
		{
		case UI_RANK_FIRST:
		case UI_RANK_SECOND:
		case UI_RANK_THIRD:
		case UI_RANK_FOUR:
		case UI_RANK_FIVE:
		case UI_RANK_SIX:
		case UI_RANK_SEVEN:
		case UI_RANK_EIGHT:
		case UI_RANK_NINE:
		case UI_RANK_LAST:
			m_apObject2D->SetTexture(CTexture::TEXTURE_RANK);
			m_bRank = true;
			break;
			//ƒtƒH[ƒ‹ƒXƒ‹[

		case UI_RANK_NEW:
			m_apObject2D->SetTexture(CTexture::TEXTURE_NEW);
			break;

		case UI_HP:
			m_apObject2D->SetTexture(CTexture::TEXTURE_HP);
			break;

		case UI_MP:
			m_apObject2D->SetTexture(CTexture::TEXTURE_MP);
			break;

		case UI_NOWSCORE:
			m_apObject2D->SetTexture(CTexture::TEXTURE_NOWSCORE);
			break;

		case UI_TUTORIAL1:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL1);
			break;

		case UI_TUTORIAL2:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL2);
			break;

		case UI_TUTORIAL3:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL3);
			break;

		case UI_TUTORIAL4:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL4);
			break;

		case UI_TUTORIAL5:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL5);
			break;

		case UI_TUTORIAL6:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL6);
			break;

		case UI_TITLELOGO:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TITLE);
			break;

		case UI_PRESS_ENTER:
			m_apObject2D->SetTexture(CTexture::TEXTURE_PRESSENTER);
			break;

		case UI_START:
			m_apObject2D->SetTexture(CTexture::TEXTURE_START);
			break;

		case UI_TUTORIAL:
			m_apObject2D->SetTexture(CTexture::TEXTURE_TUTORIAL);
			break;

		case UI_QUIT:
			m_apObject2D->SetTexture(CTexture::TEXTURE_QUIT);
			break;

		default:
			break;
		}

		m_bReverse = false;
	}

	return S_OK;
}

//
//”wŒi‚ÌI—¹ˆ—
//
void CCharUI::Uninit()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Uninit();
		CObject::Release();
	}
}

//
//”wŒi‚ÌXVˆ—
//
void CCharUI::Update()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Update();
		m_col = m_apObject2D->GetCol();

		if (m_bRank)
		{
			m_apObject2D->SetUV((1.0f / 10) * (int)m_UI, (1.0f / 10) + (1.0f / 10) * (int)m_UI, 0.0f, 1.0f);
		}

		switch (m_state)
		{
		case STATE_SELECT:
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case STATE_BLINK:
			if (m_col.a >= 0.0f && !m_bReverse)
			{
				m_col.a -= 0.04f;

				if (m_col.a <= 0.0f)
				{
					m_bReverse = true;
				}
			}

			if(m_bReverse)
			{
				m_col.a += 0.02f;

				if (m_col.a >= 1.0f)
				{
					m_bReverse = false;
				}
			}
			break;

		case STATE_INVALID:
			m_col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			break;

		case STATE_INVISIBLE:
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			break;

		default:
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		m_apObject2D->SetCol(m_col);
	}
}

//
//”wŒi‚Ì•`‰æˆ—
//
void CCharUI::Draw()
{
	if (m_apObject2D != nullptr)
	{
		m_apObject2D->Draw();
	}
}