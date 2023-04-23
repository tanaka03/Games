#include "title.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "object2d.h"

CTitle::CTitle() : m_mode(MODE_BEGIN), m_select(SELECT_GAMEPLAY)
{
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Init()
{
	m_pObj.resize(6);

	// 背景関連
	m_pObj[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "BG_STRIPE", CObject::PRIORITY_SECOND);
	m_pObj[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
	m_pObj[0]->SetAnimation(500.0f,1.0f, 5, 15, true);

	m_pObj[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "", CObject::PRIORITY_SECOND);
	m_pObj[1]->SetCol(D3DXCOLOR(0.0f,0.7f,1.0f,0.5f));

	// 文字関連
	m_pObj[2] = CObject2D::Create(D3DXVECTOR3(300.0f, 150.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4), "TITLE", CObject::PRIORITY_SECOND);
	m_pObj[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pObj[3] = CObject2D::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5), "TEXT_PRESSENTER", CObject::PRIORITY_SECOND);
	m_pObj[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pObj[4] = CObject2D::Create(D3DXVECTOR3(1500.0f, 300.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6), "TEXT_PLAYGAME", CObject::PRIORITY_SECOND);
	m_pObj[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pObj[5] = CObject2D::Create(D3DXVECTOR3(1500.0f, 500.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6), "TEXT_EXIT", CObject::PRIORITY_SECOND);
	m_pObj[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

void CTitle::Uninit()
{
}

void CTitle::Update()
{
	TextBehavior();

	if (m_mode != MODE_TRANSNEXT)
	{
		return;
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		for (auto &p : m_pObj)
		{
			p->Destroy();
		}
		m_pObj.clear();

		switch (m_select)
		{
		case CTitle::SELECT_GAMEPLAY:
			CApplication::GetInstance()->GetMode()->SetMode(MODE_GAME);
			break;

		case CTitle::SELECT_EXIT:
			// アプリケーションを終了
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}
}

void CTitle::TextBehavior()
{
	static int time = 0;
	time++;

	int select = (int)m_select;
	float alphaCol = (m_pObj[3]->GetCol().a + (1.0f / 2)) * sin(time * 0.04f);

	switch (m_mode)
	{
	case MODE_BEGIN:
		m_pObj[3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, alphaCol));

		if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
		{
			m_pObj[3]->SetMove(D3DXVECTOR3(15.0f, 0.0f, 0.0f));
			m_mode = MODE_SELECT;
		}
		break;

	case MODE_SELECT:
		if (m_pObj[4]->GetPos().x >= 1000.0f)
		{
			m_pObj[4]->SetMove(D3DXVECTOR3(-15.0f, 0.0f, 0.0f));
			m_pObj[5]->SetMove(D3DXVECTOR3(-15.0f, 0.0f, 0.0f));
		}
		else
		{
			m_pObj[4]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pObj[5]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_mode = MODE_TRANSNEXT;
		}
		break;

	case MODE_TRANSNEXT:
		if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_W))
		{
			if (select > 0)
			{
				select--;
				m_select = (ESelect)select;
			}
		}
		else if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_S))
		{
			if (select < SELECT_MAX)
			{
				select++;
				m_select = (ESelect)select;
			}
		}

		switch (select)
		{
		case CTitle::SELECT_GAMEPLAY:
			m_pObj[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pObj[5]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			break;

		case CTitle::SELECT_EXIT:
			m_pObj[4]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_pObj[5]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;

		default:
			break;
		}

		break;

	default:
		break;
	}
}